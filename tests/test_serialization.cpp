#include <catch2/catch_test_macros.hpp>
#include "student.hpp"
#include "instructor.hpp"

TEST_CASE("Student JSON serialization") {
  Student s(10,"Alice","alice@uni.edu",2027, {"CS101","HIST110"});
  auto j = s.to_json();
  CHECK(j.at("role") == "Student");
  CHECK(j.at("name") == "Alice");
  CHECK(j.at("grad_year") == 2027);
}

TEST_CASE("Instructor YAML serialization") {
  Instructor i(11,"Bob","bob@uni.edu","C-210", {"CS101"});
  auto y = i.to_yaml();
  CHECK(y["role"].as<std::string>() == "Instructor");
  CHECK(y["office"].as<std::string>() == "C-210");
}

TEST_CASE("CSV escaping handles commas and quotes") {
  Student s(12,"Eve, \"The Great\"","eve@uni.edu",2028, {"CS,101","AI\"Lab"});
  auto row = s.csv_row();
  REQUIRE(row.find("\"Eve, \"\"The Great\"\"\"") != std::string::npos);
}

TEST_CASE("Validation throws on bad email") {
  REQUIRE_THROWS_AS(Student(13,"Zed","not-an-email",2026), ValidationError);
}
TEST_CASE("Student JSON round trip")
{
    Student original(
        20,
        "Eli",
        "eli@morehouse.edu",
        2027,
        {"CS310", "MATH"}
    );

    auto json = original.to_json();

    Student copy = Student::from_json(json);

    CHECK(copy.id() == original.id());
    CHECK(copy.name() == original.name());
    CHECK(copy.email() == original.email());
    CHECK(copy.to_json() == original.to_json());
}

TEST_CASE("Instructor JSON round trip")
{
    Instructor original(
        21,
        "Professor Smith",
        "smith@morehouse.edu",
        "Wheeler Hall",
        {"CS310"}
    );

    auto json = original.to_json();

    Instructor copy = Instructor::from_json(json);

    CHECK(copy.id() == original.id());
    CHECK(copy.name() == original.name());
    CHECK(copy.email() == original.email());
    CHECK(copy.to_json() == original.to_json());
}

TEST_CASE("Student from_json rejects missing fields")
{
    nlohmann::json bad = {
        {"id", 22},
        {"name", "Eli"}
    };

    REQUIRE_THROWS_AS(
        Student::from_json(bad),
        ValidationError
    );
}