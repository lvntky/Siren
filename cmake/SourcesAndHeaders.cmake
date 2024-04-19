set(sources
    src/targalib.cpp
    src/bresenham_manager.cpp
    src/model_parser.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    include/targalib/targalib.h
    include/siren/common.hpp
    include/siren/bresenham_manager.hpp
    include/siren/model_parser.hpp
)

set(test_sources
 # src/tmp_test.cpp
)
