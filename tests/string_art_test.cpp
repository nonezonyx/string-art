#include "string_art/string_art.hpp"
#include <gtest/gtest.h>
#include <cstdlib>
#include <random>
#include <sstream>

std::random_device rd;
std::mt19937 gen(rd());

constexpr int ITERATIONS = 1000;

using namespace string_art;

namespace {
String random_string() {
    std::uniform_real_distribution<float> dist_thickness(0.0f, 10.0f);
    std::uniform_int_distribution<int> dist_color(0, 255);
    String string;
    string.color[0] = dist_color(gen);
    string.color[1] = dist_color(gen);
    string.color[2] = dist_color(gen);
    string.color[3] = dist_color(gen);
    string.thickness = dist_thickness(gen);
    return string;
}
}  // namespace

TEST(Operators, SimpleStringEquality) {
    String dafault_string;
    String green_string{.color = {0, 255, 0, 255}};
    EXPECT_TRUE(dafault_string == dafault_string);
    EXPECT_TRUE(green_string == green_string);
    EXPECT_FALSE(green_string == dafault_string);
}

TEST(Operators, RandomStringEquality) {
    for (int iteration = 0; iteration < ITERATIONS; ++iteration) {
        String string1 = random_string();
        String string2 = random_string();
        EXPECT_EQ(
            string1 == string2, string1.color == string2.color &&
                                    string1.thickness == string2.thickness
        );
        EXPECT_TRUE(string1 == string1);
        EXPECT_TRUE(string2 == string2);
        EXPECT_FALSE(string1 != string1);
        EXPECT_FALSE(string2 != string2);
    }
}

TEST(Serialization, DefaultString) {
    std::stringstream ss;
    String string;
    ss << string;
    EXPECT_EQ(ss.str(), "String(RGBA(0, 0, 0, 255), 1)");
}

TEST(Serialization, RandomString) {
    for (int iteration = 0; iteration < ITERATIONS; ++iteration) {
        String string = random_string();
        std::stringstream ss;
        ss << string;
        EXPECT_EQ(
            ss.str(), (std::stringstream{}
                       << "String(RGBA(" << string.color[2] << ", "
                       << string.color[1] << ", " << string.color[0] << ", "
                       << string.color[3] << "), " << string.thickness << ")")
                          .str()
        );
    }
}

TEST(Deserialization, DefaultString) {
    const String original;
    String deserialized;
    std::vector<std::string> strings = {
        "String(RGBA(0, 0, 0, 255), 1)",
        "String( BRGA( 0  , \t 0,0, 255\v), 1.00)",
        "String(\tRGBA(0,0,0,255),1.0)",
        " \t\n\r\nString(RGBA( 0,0,0 ,255 ) ,+1.000)",
    };
    for (const std::string &str : strings) {
        std::istringstream iss(str);
        EXPECT_TRUE(iss >> deserialized);
        EXPECT_EQ(deserialized, original);
    }
}

TEST(Deserialization, RandomString) {
    for (int iteration = 0; iteration < ITERATIONS; ++iteration) {
        String string = random_string();
        String deserialized;
        std::stringstream ss;
        ss << string;
        ss >> deserialized;
        EXPECT_EQ(deserialized, string);
    }
}

TEST(Serialization, DefaultMetadata) {
    std::stringstream ss;
    Metadata metadata;
    ss << metadata;
    EXPECT_EQ(
        ss.str(),
        "Metadata{background_color: RGBA(255, 255, 255, 255), lines: 2500, "
        "canvas_width: "
        "4096, "
        "canvas_height: 4096, pixel_length: 1, string_thickness: 1}"
    );
}

TEST(Serialization, AltColorMetadata) {
    std::stringstream ss;
    Metadata metadata{.background_color = {10, 20, 30, 40}};
    ss << metadata;
    EXPECT_EQ(
        ss.str(),
        "Metadata{background_color: RGBA(30, 20, 10, 40), lines: 2500, "
        "canvas_width: "
        "4096, "
        "canvas_height: 4096, pixel_length: 1, string_thickness: 1}"
    );
}

TEST(Deserialization, Metadata) {
    std::stringstream ss;
    Metadata metadata{.background_color = {10, 20, 30, 40}};
    ss << metadata;
    Metadata deserialized_metadata;
    EXPECT_TRUE(ss >> deserialized_metadata);
    EXPECT_EQ(deserialized_metadata, metadata);
}
