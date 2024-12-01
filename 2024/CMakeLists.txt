set(DAYS_DIR "./") 

# Ajouter tous les sous-dossiers de type day_XX
file(GLOB DAY_FOLDERS ${DAYS_DIR}/day_*)

foreach(DAY_FOLDER ${DAY_FOLDERS})
    if(EXISTS ${DAY_FOLDER}/CMakeLists.txt)
        add_subdirectory(${DAY_FOLDER})
    endif()
endforeach()