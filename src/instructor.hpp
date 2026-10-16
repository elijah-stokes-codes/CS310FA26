#pragma once
#include "person.hpp"
#include "csv.hpp"
#include <vector>

class Instructor : public Person {
  std::string office_;
  std::vector<std::string> teaches_;
public:
  Instructor(int id, std::string name, std::string email,
           std::string office,
           std::vector<std::string> teaches = {})
    : Person(id, name, email),
      office_(office),
      teaches_(teaches)
{
    if (office_.empty())
    {
        throw ValidationError("office is required");
    }
}

  std::string role() const override 
  { 
    return "Instructor"; 
}
static Instructor from_json(const nlohmann::json& j)
{
    try
    {
        if (!j.contains("id") ||
            !j.contains("name") ||
            !j.contains("email") ||
            !j.contains("office"))
        {
            throw ValidationError("Missing required Instructor field");
        }

        int id = j.at("id").get<int>();
        std::string name = j.at("name").get<std::string>();
        std::string email = j.at("email").get<std::string>();
        std::string office = j.at("office").get<std::string>();

        std::vector<std::string> teaches;

        if (j.contains("teaches"))
        {
            teaches = j.at("teaches")
                        .get<std::vector<std::string>>();
        }

        return Instructor(
            id,
            name,
            email,
            office,
            teaches
        );
    }
    catch (const ValidationError&)
    {
        throw;
    }
    catch (const std::exception&)
    {
        throw ValidationError("Invalid Instructor JSON");
    }
}

  nlohmann::json to_json() const override {
    return {
      {"role", role()},
      {"id", id_},
      {"name", name_},
      {"email", email_},
      {"office", office_},
      {"teaches", teaches_}
    };
  }

  YAML::Node to_yaml() const override {
    YAML::Node n;
    n["role"] = role();
    n["id"] = id_;
    n["name"] = name_;
    n["email"] = email_;
    n["office"] = office_;
    for (const auto& c : teaches_) n["teaches"].push_back(c);
    return n;
  }

  std::string csv_header() const override {
    return "role,id,name,email,office,teaches"; // teaches joined by ';'
  }

  std::string csv_row() const override {
    std::string joined;
    for (size_t i=0;i<teaches_.size();++i) {
      if (i) joined+=';';
      joined += teaches_[i];
    }
    return csv_escape(role()) + "," + std::to_string(id_) + "," +
           csv_escape(name_) + "," + csv_escape(email_) + "," +
           csv_escape(office_) + "," + csv_escape(joined);
  }
};