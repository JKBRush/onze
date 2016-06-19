class Lyrics{
private:
    const vector<string> _lyrics = {
        
        " OS X Cheetah ",
        " OS X Puma ",
        " OS X Jaguar ",
        " OS X Panther ",
        " OS X Tiger ",
        " OS X Leopard ",
        " OS X Snow Leopard ",
        " OS X Lion ",
        " OS X Mountain Lion ",
        " OS X Mavericks ",
        " OS X Yosemite ",
        " OS X EI Capitan ",
    };
    
public:
    string _str;
    string getNextString(){
        static int i = 0;
        if(i >= _lyrics.size()) i = 0;
        _str = _lyrics.at(i);
        i++;
        return _str;
    }
    
    const vector<string> circleLyrics = {
        
        " Mac OS ",
        " OS X ",
        " Jaguar ",
        " Tiger ",
        " Leopard ",
        " Snow Leopard ",
        " Lion ",
        " Mountain Lion ",
        " Mavericks ",
        " Yosemite ",
        " EI Capitan ",
        " 10.11.5 ",
    };
};

