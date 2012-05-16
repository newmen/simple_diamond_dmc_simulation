#include <iostream>
#include <cmath>

#include "surface.h"

#include "abshreaction.h"
#include "addhreaction.h"
#include "etchingreaction.h"
#include "migrationbridgereaction.h"
#include "addch2reaction.h"
#include "formdimerreaction.h"
#include "dropdimerreaction.h"
#include "migrationhreaction.h"
#include "reactor.h"


Surface::Surface(Crystal *crystal) : _crystal(crystal) {
    init();
}

Surface::~Surface() {
// TODO Увверен, что это нужно?
//    for (int i = 0; i < 8; i++) delete _reactions[i];
//    delete _reactions;
}

void Surface::init() {


    _crystal->init();
    _crystal->throughAllCarbonsIter(std::ref(*this));

    std::cout << "\n----------------\n";
    std::cout << "hydrocarbons: " << this->_hydroCarbons.size() << std::endl;
    std::cout << "active carbons: " << this->_activeCarbons.size() << std::endl;
    std::cout << "dimers: " << this->_dimerBonds.size() << std::endl;
    std::cout << "----------------\n\n";
}

float Surface::doReaction() {
    // жёстко, но действенно.

    AbsHReaction *abshreaction = new AbsHReaction(this);
    AddHReaction *addhreaction= new AddHReaction(this);
    EtchingReaction *etchingreaction= new EtchingReaction(this, _crystal);
    MigrationHReaction *migrationhreaction = new MigrationHReaction(this);
    AddCH2Reaction *addch2reaction = new AddCH2Reaction(this, _crystal);
    FormDimerReaction *formdimerreaction = new FormDimerReaction(this, _crystal);
    DropDimerReaction *dropdimerreaction= new DropDimerReaction(this);
    MigrationBridgeReaction *migrationbridgereaction= new MigrationBridgeReaction(this, _crystal);

    std::cout << "  ...seeAt in sets\n";

    for (Carbon *carbon : _activeCarbons) {
        addhreaction->seeAt(carbon);
        formdimerreaction->seeAt(carbon, 0);
    }

    for (Carbon *carbon : _hydroCarbons) {
        abshreaction->seeAt(carbon);
        //migrationbridgereaction->seeAt(carbon);
        etchingreaction->seeAt(carbon);
    }

    for (auto &carbons_pair : _dimerBonds) {
        // TODO: стоит пересмотреть метод SeeAt для DualReaction, в плане аргументов (чтобы принмало &pair вместо двух Carbon *)
        addch2reaction->seeAt(carbons_pair.first, carbons_pair.second);
        dropdimerreaction->seeAt(carbons_pair.first, carbons_pair.second);
        migrationhreaction->seeAt(carbons_pair.first, carbons_pair.second);
    }


    //std::cout << addhreaction->commonRate();

/*
    std::cout << "\ncall addh::commonRate\n";
    addhreaction->commonRate();
    std::cout << "\ncall absh::commonRate\n";
    abshreaction->commonRate();
    std::cout << "\ncall addch2::commonRate\n";
    addch2reaction->commonRate();
    std::cout << "\ncall formdim::commonRate\n";
    formdimerreaction->commonRate();
    std::cout << "\ncall dropdim::commonRate\n";
    dropdimerreaction->commonRate();
    std::cout << "\ncall etching::commonRate\n";
    etchingreaction->commonRate();
    std::cout << "\ncall migrh::commonRate\n";
    migrationhreaction->commonRate();
    std::cout << "\ncall mighbridge::commonRate\n";
    migrationbridgereaction->commonRate();
*/

    // TODO: порезать код представленный в этом методе на более маленькие методы, и вызывать их последовательно!

    // TODO: число 8 лучше задавать константой (в любом случае)
    double commonRates[8] = {
        addhreaction->commonRate(),
        abshreaction->commonRate(),
        addch2reaction->commonRate(),
        formdimerreaction->commonRate(),
        dropdimerreaction->commonRate(),
        etchingreaction->commonRate(),
        migrationhreaction->commonRate(),
        migrationbridgereaction->commonRate(),
    };

    std::cout << "\n ---- commonRates ------\n";
    std::cout << "AddHReaction: " << commonRates[0] << "\n";
    std::cout << "AbsHReaction: " << commonRates[1] << "\n";
    std::cout << "AddCH2Reaction: " << commonRates[2] << "\n";
    std::cout << "FormDimerReaction: " << commonRates[3] << "\n";
    std::cout << "DropDimerReaction: " << commonRates[4] << "\n";
    std::cout << "EtchingReaction: " << commonRates[5] << "\n";
    std::cout << "MigrationHReaction: " << commonRates[6] << "\n";
    std::cout << "MigrationBridgeReaction: " << commonRates[7] << "\n";
    std::cout << " -----------------------\n";

    // считаем сумму скоростей во всем реакциям.
    double sumRate = 0.0;

    for (int i = 0; i < 8; i++) sumRate += commonRates[i];

//    for (double i : commonRates) {
//        i+=sumRate;
//        std::cout << i << " ";
//    }

    std::cout << "\n    ...sumRate: " << sumRate << std::endl;

    // нормируем реакции.
    double valuetedRates[8];
    for (int i = 0; i < 8; i++) {
        valuetedRates[i] = commonRates[i] / sumRate;
    }

    // строим линию
    for (int i = 1; i < 8; i++) {
        valuetedRates[i] += valuetedRates[i-1];
    }

    // кидаем случайное число, выбираем реакцию и проводим ее.
    double reactionIndex = rand() / double(RAND_MAX) ;
    double dt = 0;

    // выбор
    // TODO:

    std::cout << "\n    ...choose reaction... ";
    if (reactionIndex < valuetedRates[0]) {
        std::cout << "addhreaction!\n";
        addhreaction->doIt();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[0];
    }
    else if (reactionIndex < valuetedRates[1]) {
        std::cout << "abshreaction!\n";
        abshreaction->doIt();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[1];
    }
    else if (reactionIndex < valuetedRates[2]) {
        std::cout << "addch2reaction!\n";
        addch2reaction->doIt();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[2];
    }
    else if (reactionIndex < valuetedRates[3]) {
        std::cout << "formdimer!\n";
        formdimerreaction->doIt();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[3];
    }
    else if (reactionIndex < valuetedRates[4]) {
        std::cout << "dropdimer!\n";
        dropdimerreaction->doIt();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[4];
    }
    else if(reactionIndex < valuetedRates[5]) {
        std::cout << "etching!\n";
        etchingreaction->doIt();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[5];
    }
    else if (reactionIndex < valuetedRates[6]) {
        std::cout << "migrH!\n";
        migrationhreaction->doIt();
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[6];
    }
    else {
        migrationbridgereaction->doIt();
        std::cout << "migrBridge!\n";
        dt = -log2(rand() / double(RAND_MAX)) / commonRates[7];
    }

    std::cout << "\ndt = " << dt << std::endl;

    delete abshreaction;
    delete addhreaction;
    delete etchingreaction;
    delete migrationhreaction;
    delete addch2reaction;
    delete formdimerreaction;
    delete dropdimerreaction;
    delete migrationbridgereaction;

    return dt;
}

void Surface::operator() (Carbon *carbon) {

    //std::cout << "call Surface::operator()\n";
    //std::cout << "this carbon properties: \n  actives: " << carbon->actives() << "\n  hydro: " << carbon->hydrogens() << "\n\n";
    if (carbon->actives() > 0) _activeCarbons.insert(carbon);
    if (carbon->hydrogens() > 0) _hydroCarbons.insert(carbon);
}

void Surface::addHydrogen(Carbon *carbon) {
    carbon->addHydrogen();
    _hydroCarbons.insert(carbon);
    if (carbon->actives() == 0) _activeCarbons.erase(carbon);
}

void Surface::removeHydrogen(Carbon *carbon) {
    carbon->absHydrogen();
    _activeCarbons.insert(carbon);
    if (carbon->hydrogens() == 0) _hydroCarbons.erase(carbon);
}

void Surface::addCarbon(Carbon *carbon, Carbon *bottomFirst, Carbon *bottomSecond) {
    _crystal->addCarbon(carbon);

    // надо ли? и так же связь остается у каждого.
    // bottomFirst->formBond();
    // bottomSecond->formBond();

    // а вот из множества димеров их исключить наверное следовало бы
    auto it = _dimerBonds.find(bottomFirst);
    if (it == _dimerBonds.end()) {
        // если не нашли по first, ищем по second
        it = _dimerBonds.find(bottomSecond);
    }

    _dimerBonds.erase(it); // удаляем димер из хеша

    bottomFirst->setAsNotDimer();
    bottomSecond->setAsNotDimer();


    _hydroCarbons.insert(carbon);
    if (bottomFirst->actives() == 0) _activeCarbons.erase(bottomFirst);
    if (bottomSecond->actives() == 0) _activeCarbons.erase(bottomSecond);
}

void Surface::removeCarbon(Carbon *carbon, Carbon *bottomFirst, Carbon *bottomSecond) {
    _crystal->removeCarbon(carbon);

    bottomFirst->dropBond();
    bottomSecond->dropBond();

    _hydroCarbons.erase(carbon); // т.к. только те, что с водородами могут отлетать (проверка внутри реакции)
    _activeCarbons.insert(bottomFirst);
    _activeCarbons.insert(bottomSecond);
}

void Surface::moveCarbon(Carbon *carbon, const int3 &to,
                         const std::pair<Carbon *, Carbon *> &fromBasis,
                         const std::pair<Carbon *, Carbon *> &toBasis)
{
    _crystal->move(carbon, to);

    /*
        надо разорвать димер так чтобы у него не было активных связей,
        т.к димерная связь идет на мостовую группу. Аналогичная ситуация
        и с образованием димера после перемещения мостовой группы.
    */

    // добавление к димерам
    // TODO: димер не образуется автоматически, при миграции мостовой группы, образуются просто активные связи
    Carbon *first = fromBasis.first;
    first->dropBond();
    _activeCarbons.insert(first);
    Carbon *second = fromBasis.second;
    fromBasis.second->dropBond();
    _activeCarbons.insert(second);
//    _dimerBonds[first] = second;



    // удаление из димеров
    first = toBasis.first;
    second = toBasis.second;
    auto it = _dimerBonds.find(first);
    if (it == _dimerBonds.end()) {
        it = _dimerBonds.find(second);
    }

    if (it != _dimerBonds.end()) {
        _dimerBonds.erase(it);
        first->setAsNotDimer();
        second->setAsNotDimer();
    } else {
        // может мигрировать не только на димеры, но и на активные атомы
        first->formBond();
        second->formBond();
    }
}


void Surface::addDimer(Carbon *first, Carbon *second) {
    _dimerBonds[first] = second;
//    _dimerBonds[second] = first;

    first->formBond();
    second->formBond();

    first->setAsDimer();
    second->setAsDimer();

    if (first->actives() == 0) _activeCarbons.erase(first);
    if (second->actives() == 0) _activeCarbons.erase(second);
}

void Surface::dropDimer(Carbon *first, Carbon *second) {
    auto it = _dimerBonds.find(first);
    if (it == _dimerBonds.end()) {
        // если не нашли по first, ищем по second
        it = _dimerBonds.find(second);
    }

    _dimerBonds.erase(it); // удаляем димер из хеша

    second->dropBond();
    first->dropBond();

    first->setAsNotDimer();
    second->setAsNotDimer();

    _activeCarbons.insert(first);
    _activeCarbons.insert(second);
}

int Surface::numberOfSites() {
    std::set<Carbon*> allSites;
    allSites.insert(_activeCarbons.begin(),_activeCarbons.end());
    allSites.insert(_hydroCarbons.begin(), _hydroCarbons.end());

    return allSites.size();
}
