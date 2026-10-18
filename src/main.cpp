#include <iostream>

#include "dataManager.hpp"
#include "udeaBook.hpp"
#include "core.hpp"
#include "Usr.hpp"

int main() {
    Usr** masterArrayUsrs = nullptr;
    Chat ** masterArrayChats = nullptr;

    size_t masterCountUsrs,
        mastercountChats,
        masterCapacityUsrs,
        masterCapacityChats;

    core::initializerAll(masterArrayUsrs,masterCountUsrs,masterCapacityUsrs,masterArrayChats,mastercountChats,masterCapacityChats);

    if(!dataManager::loadSystemData(masterArrayUsrs,masterCountUsrs,masterCapacityUsrs,masterArrayChats,mastercountChats,masterCapacityChats))return 1;

    core::registerMemoryAllocation(sizeof(Usr **)+sizeof(Usr *)* masterCapacityUsrs);
    core::registerMemoryAllocation(sizeof(Chat **)+sizeof(Chat *)* masterCapacityChats);

    char election = '0';
    Usr* currentUsr = nullptr;

    while (election != 'e' && election != 'E') {
        currentUsr = udeaBook::initSessionInterface(masterArrayUsrs, masterCountUsrs);

        if (currentUsr == nullptr) {
            continue;
        }

        do {
            election = udeaBook::usrInterface(currentUsr);

            switch (election) {
            case '1':
                udeaBook::friendsManage(currentUsr, masterArrayUsrs, masterCountUsrs);
                break;
            case '2':
                udeaBook::profileViewer(currentUsr);
                break;
            case '3':
                udeaBook::viewSugestions(currentUsr);
                break;
            case '4':
                udeaBook::msgManager(
                    currentUsr, masterArrayChats, mastercountChats, masterCapacityChats);
                break;
            }
        } while (election != 's' && election != 'S' && election != 'e' && election != 'E');
    }
    if(!dataManager::saveSystemData(masterArrayUsrs,masterCountUsrs,masterArrayChats,mastercountChats))return 1;;
    dataManager::freeSystemData(masterArrayUsrs,masterCountUsrs,masterArrayChats,mastercountChats,masterCapacityUsrs,masterCapacityChats);
    return 0;
}
