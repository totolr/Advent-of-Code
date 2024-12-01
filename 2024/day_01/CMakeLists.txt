# CMake pour le jour 1 de 2024

# Nom de l'exécutable
set(EXECUTABLE_NAME day_01)

# Spécifier le fichier source
add_executable(${EXECUTABLE_NAME} main.c)

# Si tu as des bibliothèques spécifiques à lier, tu peux les ajouter ici
# target_link_libraries(${EXECUTABLE_NAME} library_name)

# Si tu veux inclure des fichiers d'en-tête ou des fichiers supplémentaires
# target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/some_include_directory)

# Définir le répertoire de travail pour l'exécutable