cmake_minimum_required(VERSION 3.16...3.27)
project(OpNovice2)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -g")
set(CMAKE_LINKER_FLAGS     "${CMAKE_LINKER_FLAGS} -fsanitize=address")

# Geant4 の UI/Vis オプション
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

# Geant4 の include と定義を読み込む

if (MSVC)
  # 全ソースを UTF-8 としてコンパイル
  add_compile_options("/utf-8")
endif()

include(${Geant4_USE_FILE})

# ヘッダー検索パス
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${Geant4_INCLUDE_DIR}
)

# src フォルダの .cc を全て拾う
file(GLOB sources
  ${PROJECT_SOURCE_DIR}/src/*.cc
)

# include フォルダの .hh を全て拾う（IDEでの見える化用）
file(GLOB headers
  ${PROJECT_SOURCE_DIR}/include/*.hh
)

# 実行ファイルを定義。OpNovice2.cc はプロジェクトルートにあるメイン関数
add_executable(OpNovice2
  OpNovice2.cc
  ${sources}
  ${headers}
)

# Geant4 ライブラリとリンク
target_link_libraries(OpNovice2 ${Geant4_LIBRARIES})

# マクロやスクリプトのコピー設定（必要に応じて）……
set(OpNovice2_SCRIPTS
  vis.mac
  boundary.mac
  # …その他 .mac ファイル
)

foreach(_script ${OpNovice2_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
  )
endforeach()

install(TARGETS OpNovice2 DESTINATION bin)
