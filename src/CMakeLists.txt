set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(header_path_include ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set(header_path ${CMAKE_CURRENT_SOURCE_DIR}/../include/QModernGrids)

include_directories(${header_path_include})

add_definitions(-DQMODERNGRIDS_LIBRARY)

set(source-decorators
	${header_path}/Decorators/QmgObjectdataModelDecorator.h
	${header_path}/Decorators/QmgHeaderdataModelDecorator.h
	${header_path}/Decorators/QmgFetchmoreDecorator.h
	${header_path}/Decorators/QmgDataModelDecorator.h
	${header_path}/Decorators/QmgSetDataModelDecorator.h
	${header_path}/Decorators/QmgColumnModelDecorator.h
	${header_path}/Decorators/QmgCheckboxMultimarkModelDecorator.h
	${header_path}/Decorators/QmgAlternateRowshadingModelDecorator.h
	Decorators/QmgObjectdataModelDecorator.cpp
	Decorators/QmgHeaderdataModelDecorator.cpp
	Decorators/QmgFetchmoreDecorator.cpp
	Decorators/QmgDataModelDecorator.cpp
	Decorators/QmgSetDataModelDecorator.cpp
	Decorators/QmgColumnModelDecorator.cpp
	Decorators/QmgCheckboxMultimarkModelDecorator.cpp
	Decorators/QmgAlternateRowshadingModelDecorator.cpp)
source_group("Decorators" FILES ${source-decorators})

set(source-builders
	${header_path}/Builders/QmgSourceModelBuilder.h
	${header_path}/Builders/QmgModelBuilder.h
	${header_path}/Builders/QmgHeaderdataModelBuilder.h
	${header_path}/Builders/QmgDataModelBuilder.h
	${header_path}/Builders/QmgCommonModelBuilder.h
	${header_path}/Builders/QmgColumnModelBuilder.h
	${header_path}/Builders/QmgColumnCollectionBuilder.h
	Builders/QmgSourceModelBuilder.cpp
	Builders/QmgModelBuilder.cpp
	Builders/QmgHeaderDataModelBuilder.cpp
	Builders/QmgDataModelBuilder.cpp
	Builders/QmgCommonModelBuilder.cpp
	Builders/QmgColumnModelBuilder.cpp
	Builders/QmgColumnCollectionBuilder.cpp)
source_group("Builders" FILES ${source-builders})

set(source-root
    ${header_path}/QmgPrivate.h
	${header_path}/QmgProxyModelUtils.h
	${header_path}/QmgObservableVariantListProxy.h
	${header_path}/QmgObservableVariantListModel.h
	${header_path}/QmgObservableList.h
	${header_path}/QmgModelLogger.h
	${header_path}/QmgEventHandler.h
	QmgProxyModelUtils.cpp
	QmgObservableVariantListModel.cpp
	QmgModelLogger.cpp)
source_group("" FILES ${source-root})

set(src 
    ${source-decorators} 
    ${source-builders} 
    ${source-root})

# Bind to qt
find_package(Qt5Core)
find_package(Qt5Widgets)

if(Qt5Core_FOUND AND Qt5Widgets_FOUND)
    set (EXTRA_LIBS ${EXTRA_LIBS} Qt5::Core Qt5::Widgets)    
else()
    find_package(Qt4 REQUIRED QtCore QtGui)
    set (EXTRA_LIBS ${EXTRA_LIBS} Qt4::QtCore Qt4::QtGui)
endif()

set(needed_features
    cxx_auto_type
    cxx_nullptr
    cxx_override
    cxx_lambdas)

add_library(QModernGrids SHARED ${src})
target_compile_features(QModernGrids PRIVATE ${needed_features})
target_include_directories(QModernGrids PUBLIC ${header_path_include}
										   ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(QModernGrids ${EXTRA_LIBS})