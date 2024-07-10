cmake_minimum_required(VERSION 3.15) # Проверка версии CMake.
									 # Если версия установленой программы
									 # старее указаной, произайдёт аварийный выход.

set(PROJECT_NAME Tower_Defense) # задать значение PROJECT_NAME		 
project("${PROJECT_NAME}")           # установить имя проекта


set(CMAKE_CXX_STANDARD 17)			 # устанавливаем 17 стандарт языка
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories("src/include/")
include_directories("include/")			#Добавляем хедеры
link_directories("lib/")			#Добавляем путь где находятся библиотеки

file(GLOB PROJECTSOURCES "src/*.cpp" "src/include/*.hpp")	#Ищем все cpp hpp файлы

# Сказать программе, что должен быть исполняемый файл
add_executable("${PROJECT_NAME}" mainExample.cpp ${PROJECTSOURCES})

file(COPY "resources" DESTINATION "/")	#Копируем ресурсы для exe
file(COPY "bin/" DESTINATION "Debug/")	#Копируем dll в папку с exe
#Добавляем библиотеки
target_link_libraries("${PROJECT_NAME}" 
		sfml-graphics-d
		sfml-window-d
		sfml-audio-d
		sfml-network-d
		sfml-system-d
		sfml-main-d)

#Устанавливаем в качестве запускаемого проекта наш проект
set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}")