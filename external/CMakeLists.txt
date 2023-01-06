include(FetchContent)

if (NOT USE_SYSTEM_DEPS)
    # EnTT
    FetchContent_Declare(EnTT
        URL https://github.com/skypjack/entt/archive/refs/tags/v3.11.1.zip
        URL_HASH SHA256=7cd55b71d6432f03436ee724e8b461a4099b6c749aeec0c3bc5af5893ed5b61a
        OVERRIDE_FIND_PACKAGE
    )
    FetchContent_MakeAvailable(EnTT)

    # SFML
    FetchContent_Declare(SFML
        URL https://github.com/SFML/SFML/archive/718195bf25eb747a549207daf734976a44ec6545.zip
        URL_HASH SHA256=633b6a3b9fd65ca0e7e84e4d1ea87b553dde2e3b12479ca8e6ffcf4cb5de81fa
        OVERRIDE_FIND_PACKAGE
    )
    set(BUILD_SHARED_LIBS OFF)
    set(SFML_BUILD_NETWORK OFF)
    FetchContent_MakeAvailable(SFML)
endif()
