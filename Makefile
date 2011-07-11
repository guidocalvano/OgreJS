
include common.mk
include Makefile.ogrejs

TEST = $(BINPATH)/test/main.exe
TEST_OBJPATH = $(OBJPATH)/test
TEST_OBJECTS = $(TEST_OBJPATH)/main.o
TEST_INTERNAL_CXXFLAGS = $(OGREJS_CXXFLAGS) $(CXXFLAGS)

TEST_LDFLAGS = -lws2_32 -lwinmm


test: $(TEST)

$(TEST): $(TEST_OBJECTS) $(LIBOGREJS) $(LIBV8) $(LIBOGRE) 
	$(CXX) -o "$@" $^   \
    $(TEST_LDFLAGS)   \
    $(OGREJS_LDFLAGS)   \
    $(V8_LDFLAGS)     \
    $(OGRE_LDFLAGS)   \
    $(LDFLAGS) 



$(TEST_OBJPATH)/main.o: $(SRCPATH)/test/main.cpp
	$(CXX) -c -o "$@" $^ $(TEST_INTERNAL_CXXFLAGS)

clean.test:
	$(RM) $(TEST_OBJECTS) $(TEST)
