
class ElizaChat {

    static int          num_chats=0;
    private String      _keyWordList[];
    private String      _responseList[];
    private int         _idx=0;
    private int         _rIdx=0;
    private boolean     _started=false;
    private boolean     _kw=true;
    public String       _response;
    private String      _dbKeyWord;
    public int          _widx = 0;
    public int          _w = 0;
    public int          _x;
    private char        _space;
    private char        _plus;

    public ElizaChat() {
        num_chats++;
        _keyWordList= new String[20];
        _responseList=new String[20];
        _rIdx=0;
        _idx=0;
        _keyWordList[_idx]=" ";

        _space=" ".charAt(0);
        _plus="+".charAt(0);
    }

    public String converse(String kw_) {
        _response = null;
        for(int i=0; i <= _idx - 1;i++){
            _dbKeyWord = _keyWordList[i];

            if(kw_.length()>=_dbKeyWord.length()&&_keyWordList[i].equals(kw_.substring(0,_dbKeyWord.length()))) {

                _widx = (int) Math.round(Math.random()*_rIdx-.5);
                _response = _responseList[_widx];
                _x=_response.indexOf("*");
                if(_x>0)   {
                    _response=_response.substring(0,_x)+kw_.substring(_dbKeyWord.length(),kw_.length());
                    if(_x<_responseList[_widx].length()-1)
                        _response=_response+"?";
                    _response=Eliza.ChatConj.conjugate(_response,_x);
                    _response=_response.replace(_plus,_space);
                }
                break;
            }
        }

        return _response;
    }

    public void loadresponse(String rw_){
        _responseList[_rIdx]=rw_;
        _rIdx++;
    }

    public void loadkeyword(String kw_){
        _keyWordList[_idx]=kw_;
        _idx++;
    }
}

