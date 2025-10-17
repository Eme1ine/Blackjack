
#include "View/ServicesView.hpp"
#include "View/View.hpp"
#include <QLabel>
#include <QSequentialAnimationGroup>

#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>

#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QEasingCurve>
#include <QTimer>
#include <memory>
#include <iostream>

using namespace std;

void ServicesView::dealBankSequential(QHBoxLayout *layout, const QVector<QPixmap> &pix, int idx, View *window)
{
    if (pix.size() == 0)
    {
        emit window->turnFinished();
        return;
    }
    if (idx >= pix.size())
    {
        emit window->turnFinished();
        return;
    }

    QParallelAnimationGroup *g = addCardFromRight(layout, pix[idx], window);

    window->connect(g, &QParallelAnimationGroup::finished, window, [=]()
                    { QTimer::singleShot(0, window, [=]()
                                         { dealBankSequential(layout, pix, idx + 1, window); }); });

    g->start(QAbstractAnimation::DeleteWhenStopped);
}

QParallelAnimationGroup *ServicesView::addCardFromRight(QHBoxLayout *targetLayout, const QPixmap &pix, View *window)
{

    const int cardH = pix.height();
    const int cardW = pix.width();

    // Groupe d'animations
    auto *group = new QParallelAnimationGroup(window);

    struct Clone
    {
        QLabel *clone;
        QLabel *original;
    };
    QVector<Clone> clones;
    clones.reserve(targetLayout->count());
    for (int i = 0; i < targetLayout->count(); ++i)
    {
        QLabel *tm_card_label_ptr = dynamic_cast<QLabel *>(targetLayout->itemAt(i)->widget());
        tm_card_label_ptr->setVisible(false);
        QLabel *card_label_ptr = new QLabel(window);
        card_label_ptr->setPixmap(tm_card_label_ptr->pixmap());
        card_label_ptr->setFixedHeight(cardH);
        card_label_ptr->raise();

        // Position depart
        const QPoint absPos = tm_card_label_ptr->mapTo(window, QPoint(0, 0));
        const int startX = absPos.x() - 5;
        const int endX = startX - cardW / 2;
        const int posY = absPos.y();
        card_label_ptr->move(startX, posY);
        card_label_ptr->show();

        // Animation deplacement
        auto *move = new QPropertyAnimation(card_label_ptr, "pos");
        move->setDuration(1000);
        move->setStartValue(QPoint(startX, posY));
        move->setEndValue(QPoint(endX, posY));
        move->setEasingCurve(QEasingCurve::OutCubic);
        group->addAnimation(move);
        clones.push_back({card_label_ptr, tm_card_label_ptr});
    }

    // Carte flottante
    QLabel *card = new QLabel(window);
    card->setPixmap(pix);
    card->setFixedHeight(cardH);
    card->raise();

    // Position depart
    const int startX = window->width();
    QWidget *parent = dynamic_cast<QWidget *>(targetLayout->parent());
    const QPoint absPos = parent->mapTo(window, QPoint(0, 0));
    const int endX = absPos.x() + parent->width() / 2 - cardW / 2 + cardW / 2 * targetLayout->count() + 5 * targetLayout->count();
    const int posY = absPos.y() + parent->height() / 2 - cardH / 2;

    card->move(startX, posY);
    card->show();

    // Animation deplacement
    auto *move = new QPropertyAnimation(card, "pos");
    move->setDuration(1000);
    move->setStartValue(QPoint(startX, posY));
    move->setEndValue(QPoint(endX, posY));
    move->setEasingCurve(QEasingCurve::OutCubic);

    group->addAnimation(move);
    QHBoxLayout *layout = targetLayout;

    window->connect(group, &QParallelAnimationGroup::finished, window, [window, card, layout, clones]()
                    {
        if (!layout) return;
        // Copie de la pixmap
        const QPixmap px = card->pixmap();
        card->deleteLater();

        QWidget* parent = layout->parentWidget();
        if (!parent)
        {
            parent = window;
        }

        auto* finalCard = new QLabel(parent);
        finalCard->setPixmap(px);
        finalCard->setStyleSheet("background: transparent;");

        layout->addWidget(finalCard);
        finalCard->show();
        // supprimer les clones et re-afficher les originaux (toujours dans le layout)
        for (const auto& cl : clones) {
            if(cl.clone) delete cl.clone;
            if(cl.original != nullptr) cl.original->setVisible(true);
        } });
    return group;
}

void ServicesView::updatePerson(vector<shared_ptr<Card>> cards, QHBoxLayout *layout_person, View *window)
{
    QLayoutItem *item;
    int size = cards.size();
    if (size == 0)
    {
        while ((item = layout_person->takeAt(0)) != nullptr)
        {
            delete item->widget();
            delete item;
        }
        emit window->turnFinished();
    }
    else
    {
        auto *seq = new QSequentialAnimationGroup(window);
        int nb_element = layout_person->count();
        QVector<QPixmap> toAdd;
        toAdd.reserve(size - nb_element);
        for (int i = nb_element; i < size; ++i)
        {
            auto card_ptr = cards.at(i);
            toAdd.push_back(renderSvg(card_ptr->Get_Name(), QSize(100, 200)));
        }

        dealBankSequential(layout_person, toAdd, 0, window);
    }
}

QPixmap ServicesView::renderSvg(const std::string name, const QSize &outSize)
{
    QSvgRenderer renderer(QString::fromStdString("img/" + name + ".svg"));
    if (!renderer.isValid())
        return {};

    QImage full(outSize, QImage::Format_ARGB32_Premultiplied);
    full.fill(Qt::transparent);
    {
        QPainter p(&full);
        renderer.render(&p, QRectF(QPointF(0, 0), outSize));
    }

    return QPixmap::fromImage(full);
}