
#include "View/View.hpp"
#include "Model/Person/Bank.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>
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

View::View(QWidget *parent)
    : QWidget(parent),
      bank_cards(),
      player_cards(),
      background("img/0_background.jpg")
{
    resize(500, 500);
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    // ----- Section du haut (banque) -----
    QWidget *bankSection = new QWidget(this);
    bankSection->setMinimumHeight(200);
    bankSection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    bank_cards = new QHBoxLayout(bankSection);
    bank_cards->setSpacing(8);
    bank_cards->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(bankSection, 1);

    // ----- Section du bas (joueur) -----
    QWidget *playerSection = new QWidget(this);
    playerSection->setMinimumHeight(200);
    playerSection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    player_cards = new QHBoxLayout(playerSection);
    player_cards->setSpacing(8);
    player_cards->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(playerSection, 1);

    setWindowTitle("MyWindow Example");
    setFocusPolicy(Qt::StrongFocus);
}

View::~View()
{
    cout << "View Destroy" << endl;
}

void View::dealBankSequential(QHBoxLayout *layout, const QVector<QPixmap> &pix, int idx)
{
    if (idx >= pix.size())
        return;

    QParallelAnimationGroup *g = addCardFromRight(layout, pix[idx]);

    connect(g, &QParallelAnimationGroup::finished, this, [=]()
            { QTimer::singleShot(0, this, [=]()
                                 { dealBankSequential(layout, pix, idx + 1); }); });

    g->start(QAbstractAnimation::DeleteWhenStopped);
}

QParallelAnimationGroup *View::addCardFromRight(QHBoxLayout *targetLayout, const QPixmap &pix)
{

    const int cardH = pix.height();
    const int cardW = pix.width();

    // Groupe d'animations
    auto *group = new QParallelAnimationGroup(this);

    struct Clone
    {
        QLabel *clone;
        QLabel *original;
    };
    QVector<Clone> clones;
    clones.reserve(targetLayout->count());
    for (int i = 0; i < targetLayout->count(); ++i)
    {
        cout << "On passe dans les children" << endl;
        QLabel *tm_card_label_ptr = dynamic_cast<QLabel *>(targetLayout->itemAt(i)->widget());
        tm_card_label_ptr->setVisible(false);
        QLabel *card_label_ptr = new QLabel(this);
        card_label_ptr->setPixmap(tm_card_label_ptr->pixmap());
        card_label_ptr->setFixedHeight(cardH);
        card_label_ptr->raise();

        // Position depart
        const QPoint absPos = tm_card_label_ptr->mapTo(this, QPoint(0, 0));
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
    QLabel *card = new QLabel(this);
    card->setPixmap(pix);
    card->setFixedHeight(cardH);
    card->raise();

    // Position depart
    const int startX = width();
    QWidget *parent = dynamic_cast<QWidget *>(targetLayout->parent());
    const QPoint absPos = parent->mapTo(this, QPoint(0, 0));
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

    connect(group, &QParallelAnimationGroup::finished, this, [this, card, layout, clones]()
            {
        if (!layout) return;
        // Copie de la pixmap
        const QPixmap px = card->pixmap();
        card->deleteLater();
        cout<<"finished"<<endl;

        QWidget* parent = layout->parentWidget();
        if (!parent) parent = this;

        auto* finalCard = new QLabel(parent);
        finalCard->setPixmap(px);
        finalCard->setStyleSheet("background: transparent;");

        layout->addWidget(finalCard);
        finalCard->show();
        // supprimer les clones et re-afficher les originaux (toujours dans le layout)
        for (const auto& cl : clones) {
            delete cl.clone;
            cl.original->setVisible(true);
        } });
    return group;
}

void View::updatePerson(const Person &person, QHBoxLayout *layout_person)
{
    QLayoutItem *item;
    int size = person.Get_Cards().size();
    if (size == 0)
    {
        while ((item = layout_person->takeAt(0)) != nullptr)
        {
            delete item->widget();
            delete item;
        }
    }
    else
    {
        auto *seq = new QSequentialAnimationGroup(this);
        int nb_element = layout_person->count();
        QVector<QPixmap> toAdd;
        toAdd.reserve(size - nb_element);
        for (int i = nb_element; i < size; ++i)
        {
            auto card_ptr = person.Get_Cards().at(i);
            toAdd.push_back(renderSvg(card_ptr->Get_Name(), QSize(100, 200)));
        }

        dealBankSequential(layout_person, toAdd, 0);
    }
}
void View::updateBank(const Bank &bank)
{
    updatePerson(bank, bank_cards);
}

void View::updatePlayer(const Player &player)
{
    updatePerson(player, player_cards);
}

void View::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        emit enterPressed(); // envoie le signal
    else if (event->key() == Qt::Key_S)
    {
        emit letterPressed('s');
    }
    else if (event->key() == Qt::Key_H)
    {
        emit letterPressed('h');
    }
    else
        QWidget::keyPressEvent(event);
}

QPixmap View::renderSvg(const std::string name, const QSize &outSize)
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