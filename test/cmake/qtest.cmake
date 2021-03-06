set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core)
find_package(Qt5Test)
find_package(Qt5Widgets)

if(Qt5Core_FOUND AND Qt5Widgets_FOUND AND Qt5Test_FOUND)
    set (EXTRA_LIBS ${EXTRA_LIBS} Qt5::Core Qt5::Widgets Qt5::Test)    
else()
    find_package(Qt4 REQUIRED QtCore QtGui QtTest)
    set (EXTRA_LIBS ${EXTRA_LIBS} Qt4::QtCore Qt4::QtGui Qt4::QtTest)
endif()