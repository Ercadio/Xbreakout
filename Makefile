CXX = @g++ -std=c++17
CXXFLAGS = -Wall -MMD -O -g
SOURCES = $(shell find * -type f \( -name "*.cpp" -not -name "*.test.cpp" \) )
TEST_SOURCES = $(shell find * -type f -name "*.cpp" -not -name "main.cpp")
EXEC=breakout
TEST_EXEC=test

# All of our object & dependency files are in OBJDIR
OBJDIR=build
OBJECTS = $(addprefix $(OBJDIR)/, ${SOURCES:.cpp=.o})		# .o files depend upon .cpp files with same names
TEST_OBJECTS = $(addprefix $(OBJDIR)/, ${TEST_SOURCES:.cpp=.o})
DEPENDS = ${OBJECTS:.o=.d}
TEST_DEPENDS = ${TEST_OBJECTS:.o=.d}

$(EXEC): $(DEPENDS) $(OBJECTS) $(TEST_EXEC)
	-include ${DEPENDS}
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

$(TEST_EXEC): tags $(TEST_DEPENDS) $(TEST_OBJECTS)
	-include ${DEPENDS}
	$(CXX) $(CXXFLAGS) $(TEST_OBJECTS) -o $(TEST_EXEC)
	@./$(TEST_EXEC)

# Create obj directory
$(OBJDIR):
	@echo "Creating object directory"
	@mkdir $(OBJDIR)
	@echo "Creating directory structure"
	@find . -type d ! -name $(OBJDIR) -exec mkdir -p -- $(OBJDIR)/{} \;

# Create object files from cc files
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@echo "Creating object file "$@
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJDIR)/%.d: %.cpp | $(OBJDIR)
	@echo "Creating dependency file "$@
	$(CXX) $(CXXFLAGS) -MM $< -MF $@

.PHONY: clean
clean:
	@rm -rf $(OBJDIR)

.PHONY: tags
tags:
	@ctags -R . || echo "Warning: ctags either doesn't exist or doesn't support recursive search"

.PHONY: doc
doc:
	@doxygen

