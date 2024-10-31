add_rules("mode.debug", "mode.release")

add_requires("minifb")

target("host")
    set_kind("binary")
    add_files("src/*.c")
    add_packages("minifb")
    add_includedirs("src/external")
    if is_plat("wasm") then
        set_extension(".mjs")
        add_ldflags("-sASYNCIFY -sSINGLE_FILE -sEXPORTED_RUNTIME_METHODS=writeArrayToMemory,UTF8ToString")
    end
