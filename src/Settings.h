#ifndef NOON_SETTINGS_H
#define NOON_SETTINGS_H

namespace Noon{
    class Settings{
    public:
        static Settings& instance(){
            static Settings instance;
            return instance;
        }
        bool verbose(){return verbose_;}
        void verbose(bool v){ verbose_=v;}
    private:
        Settings();
        Settings(Settings const&);
        bool verbose_;
        void operator=(Settings const&);
    };
}
#endif
