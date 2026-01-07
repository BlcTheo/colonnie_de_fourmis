cmake_minimum_required(VERSION 3.10)
project(ColonieFourmis)

# --- Configuration du compilateur ---
# Le projet impose le C++ (C++17 est recommandé pour la STL moderne)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Recherche de la bibliothèque SFML (Version 3 pour Arch) ---
# On demande explicitement les composants nécessaires
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# --- Liste des fichiers sources ---
# On regroupe tous les .cpp en suivant ton arborescence
set(SOURCES
    main.cpp
    
    # Logique et Système
    system/system/CSystem.cpp
    
    # Affichage Graphique
    system/display/CDisplay.cpp
    
    # Entités (Héritage et Polymorphisme)
    Ants/CAnt.cpp
    Ants/Worker/CWorker.cpp
    Ants/Queen/CQueen.cpp
    resources/foods/CFood.cpp
)

# --- Création de l'exécutable ---
add_executable(ColonieFourmis ${SOURCES})

# --- Liens avec les bibliothèques SFML ---
# Utilisation des cibles SFML 3 (SFML::...)
target_link_libraries(ColonieFourmis 
    SFML::Graphics 
    SFML::Window 
    SFML::System
)

# --- Inclusion des répertoires ---
# Permet de simplifier les #include dans ton code
target_include_directories(ColonieFourmis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# --- Optionnel : Copie des ressources ---
# Si tu ajoutes des images ou des sons plus tard dans un dossier "assets"
# add_custom_command(TARGET ColonieFourmis POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#    ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:ColonieFourmis>/assets)