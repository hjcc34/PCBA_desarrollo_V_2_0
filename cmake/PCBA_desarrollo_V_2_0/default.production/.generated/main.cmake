include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(PCBA_desarrollo_V_2_0_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(PCBA_desarrollo_V_2_0_default_default_XC8_FILE_TYPE_assemble)
add_library(PCBA_desarrollo_V_2_0_default_default_XC8_assemble OBJECT ${PCBA_desarrollo_V_2_0_default_default_XC8_FILE_TYPE_assemble})
    PCBA_desarrollo_V_2_0_default_default_XC8_assemble_rule(PCBA_desarrollo_V_2_0_default_default_XC8_assemble)
    list(APPEND PCBA_desarrollo_V_2_0_default_library_list "$<TARGET_OBJECTS:PCBA_desarrollo_V_2_0_default_default_XC8_assemble>")

endif()

# Handle files with suffix S, for group default-XC8
if(PCBA_desarrollo_V_2_0_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(PCBA_desarrollo_V_2_0_default_default_XC8_assemblePreprocess OBJECT ${PCBA_desarrollo_V_2_0_default_default_XC8_FILE_TYPE_assemblePreprocess})
    PCBA_desarrollo_V_2_0_default_default_XC8_assemblePreprocess_rule(PCBA_desarrollo_V_2_0_default_default_XC8_assemblePreprocess)
    list(APPEND PCBA_desarrollo_V_2_0_default_library_list "$<TARGET_OBJECTS:PCBA_desarrollo_V_2_0_default_default_XC8_assemblePreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC8
if(PCBA_desarrollo_V_2_0_default_default_XC8_FILE_TYPE_compile)
add_library(PCBA_desarrollo_V_2_0_default_default_XC8_compile OBJECT ${PCBA_desarrollo_V_2_0_default_default_XC8_FILE_TYPE_compile})
    PCBA_desarrollo_V_2_0_default_default_XC8_compile_rule(PCBA_desarrollo_V_2_0_default_default_XC8_compile)
    list(APPEND PCBA_desarrollo_V_2_0_default_library_list "$<TARGET_OBJECTS:PCBA_desarrollo_V_2_0_default_default_XC8_compile>")

endif()


# Main target for this project
add_executable(PCBA_desarrollo_V_2_0_default_image_pQ_dhEuw ${PCBA_desarrollo_V_2_0_default_library_list})

set_target_properties(PCBA_desarrollo_V_2_0_default_image_pQ_dhEuw PROPERTIES
    OUTPUT_NAME "default-production"
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${output_extensions}"
    RUNTIME_OUTPUT_DIRECTORY "${PCBA_desarrollo_V_2_0_default_output_dir}")
target_link_libraries(PCBA_desarrollo_V_2_0_default_image_pQ_dhEuw PRIVATE ${PCBA_desarrollo_V_2_0_default_default_XC8_FILE_TYPE_link})

# Add the link options from the rule file.
PCBA_desarrollo_V_2_0_default_link_rule( PCBA_desarrollo_V_2_0_default_image_pQ_dhEuw)


