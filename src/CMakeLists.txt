project(agrimarkets)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( agrimarkets agrimarkets agrimarkets.cpp )
target_include_directories( agrimarkets PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( agrimarkets ${CMAKE_SOURCE_DIR}/../ricardian )