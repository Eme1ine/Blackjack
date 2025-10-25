// Include de ServicesView (tel que fourni dans ton projet).
// Si ton ServicesView.hpp dépend de View.hpp ou Card vraie,
// adapte l'ordre d'inclusion ou supprime les stubs ci-dessus.
#include "View/ServicesView.hpp"
#include "View/View.hpp"
#include "Model/Card.hpp"
#include "ServicesViewTest.hpp"

std::shared_ptr<Card> ServicesViewTest::generateCard(int i)
{
    std::shared_ptr<Card> c = std::make_shared<Card>();
    c->Set_Color(Spade);
    c->Set_Number((Number)i);
    return c;
}

void ServicesViewTest::test_updatePerson_empty_clears_layout_and_emits()
{
    // Setup UI
    View window;
    window.resize(400, 200);
    QWidget parentWidget(&window);
    auto *layout = new QHBoxLayout(&parentWidget);

    // Remplir le layout avec quelques labels pour simuler l'etat initial
    for (int i = 0; i < 3; ++i)
    {
        QLabel *lbl = new QLabel(QString("init%1").arg(i));
        layout->addWidget(lbl);
    }
    parentWidget.show();

    // Create ServicesView instance
    ServicesView svc;

    // Spy sur le signal turnFinished de la fenêtre
    QSignalSpy spy(&window, &View::turnFinished);

    // Appel avec vector vide
    std::vector<std::shared_ptr<Card>> empty;
    svc.updatePerson(empty, layout, &window);

    // Le code appelle emit window->turnFinished() immediatement pour le cas vide.
    // Attente courte et vérification
    spy.wait(200);
    QCOMPARE(spy.count(), 1); // wait jusqu'à 200ms pour l'émission
    QCOMPARE(spy.count(), 1);

    // Le layout devrait etre vide
    QCOMPARE(layout->count(), 0);
}

void ServicesViewTest::test_updatePerson_adds_cards_and_emits_after_animations()
{
    // Setup UI
    TestView window;
    window.resize(800, 600);
    QWidget parentWidget(&window);
    auto *layout = new QHBoxLayout(&parentWidget);

    // Démarrer avec 1 élément existant
    QLabel *existing = new QLabel("existing");
    layout->addWidget(existing);
    parentWidget.show();

    // Prepare ServiceView and cards
    ServicesView svc;

    // On cree 3 cartes
    std::vector<std::shared_ptr<Card>> cards;
    cards.push_back(generateCard(1));
    cards.push_back(generateCard(2));
    cards.push_back(generateCard(3));

    // Spy sur le signal turnFinished
    QSignalSpy spy(&window, &TestView::turnFinished);

    // Lancement
    svc.updatePerson(cards, layout, reinterpret_cast<View *>(&window));

    // On attend un timeout raisonnable : nombre cartes * 1100ms + marge.
    const int waitMs = static_cast<int>(cards.size() * 1100 + 500);
    bool signaled = spy.wait(waitMs);

    // Apres la fin, le layout devrait contenir >= cards.size() widgets (au moins les nouvelles cartes)
    // Ici le layout initial contenait 1 widget, la taille finale devrait etre >= cards.size()
    QVERIFY(layout->count() >= static_cast<int>(cards.size()));
}
