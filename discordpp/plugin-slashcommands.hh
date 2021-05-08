#pragma once

namespace discordpp {
    template<class BASE>
    class PluginSlashCommands : public BASE, virtual BotStruct {
    public:
        struct ApplicationCommand {
            struct Option {
                struct Choice {
                    std::string name;
                    std::variant<std::string, int> value;
                };
                enum Type {
                    SUB_COMMAND = 1,
                    SUB_COMMAND_GROUP = 2,
                    STRING = 3,
                    INTEGER = 4,
                    BOOLEAN = 5,
                    USER = 6,
                    CHANNEL = 7,
                    ROLE = 8,
                    MENTIONABLE = 9
                };
                Type type;
                std::string name;
                std::string description;
                std::optional<bool> required;
                std::optional<std::vector<Choice>> choices;
                std::optional<std::vector<Option>> options;
            };
            snowflake id;
            snowflake application_id;
            std::string name;
            std::string description;
            std::optional<std::vector<Option>> options;
            std::optional<bool> default_permission;
        };
    protected:
        void runctd() override {
            handlers.insert({"READY", [this](const json &data) {
                //self = data["user"];
                //_application_id = data["application"];
                _application_id = data["application"]["id"].get<std::string>();
            }});
            handlers.insert({"INTERACTION_CREATE", [this/*, &self*/](const json &msg) {}});
            BASE::runctd();
        }

    private:
        std::string _application_id;
    };
}