#include "parser.h"
#include "entity.h"
#include <string>
#include <vector>
#include <cassert>
#include <map>
#include <stdexcept>
#include <limits>

std::map<double, std::vector<double> > b_trajectory{
    { 1.0, { std::numeric_limits<double>::max(), std::numeric_limits<double>::max() } },
    { 1.1, { std::numeric_limits<double>::max(), std::numeric_limits<double>::max() } },
    { 1.2, { 1.5, 1.5 } },
    { 1.3, { std::numeric_limits<double>::max(), std::numeric_limits<double>::max() } }
};

std::map<double, std::vector<double> > a_trajectory{
    { 1.0, { 1.0, 1.0 } },
    { 1.1, { 2.0, 2.0 } },
    { 1.2, { std::numeric_limits<double>::max(), std::numeric_limits<double>::max() } },
    { 1.3, { 3.0, 5.55 } }
};

void should_parse_correctly() {
    std::string source("test_data");
    std::string path("test/fixtures");

    std::vector<Entity> entities = parse_data(source, path);

    for (unsigned int i = 0; i < entities.size(); i++) {
        if (entities[i].id == 2) {
            assert(entities[i].trajectories == b_trajectory);
        } else {
            assert(entities[i].trajectories == a_trajectory);
        }
    }
}

void should_throw_an_error_as_file_not_found() {
    std::string source("not_exist");
    std::string path("test/fixtures");

    try {
        parse_data(source, path);
        throw std::logic_error("Should throw an error as file does not exist.");
    } catch(const std::invalid_argument &err) {
        assert(err.what() == std::string("File doesn't exist!"));
    }
}

int main() {
    should_parse_correctly();
    should_throw_an_error_as_file_not_found();

    return 0;
}