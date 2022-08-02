
class ElizaConjugate {

    public String   _text;
    private String  _conjugate[][];

    public ElizaConjugate () {


        _conjugate=new String[13][2];
        _conjugate[0][0]=" are ";
        _conjugate[1][0]=" am ";
        _conjugate[2][0]=" were ";
        _conjugate[3][0]=" was ";
        _conjugate[4][0]=" you ";
        _conjugate[5][0]=" your ";
        _conjugate[6][0]=" my ";
        _conjugate[7][0]=" ive ";
        _conjugate[8][0]=" youve ";
        _conjugate[9][0]=" im ";
        _conjugate[10][0]=" me ";
        _conjugate[11][0]=" us ";
        _conjugate[12][0]=" we ";
        _conjugate[0][1]=" am+";
        _conjugate[1][1]=" are+";
        _conjugate[2][1]=" was+";
        _conjugate[3][1]=" were+";
        _conjugate[4][1]=" I+";
        _conjugate[5][1]=" my+";
        _conjugate[6][1]=" your+";
        _conjugate[7][1]=" you've ";
        _conjugate[8][1]=" I've+";
        _conjugate[9][1]=" you're+";
        _conjugate[10][1]=" you+";
        _conjugate[11][1]=" you+";
        _conjugate[12][1]=" you+";
    }

    public String conjugate(String text_, int x_) {
        _text=text_;
        for(int j=0;j<_conjugate.length;j++)  {
            int _w=text_.indexOf(_conjugate[j][0],x_);
            if(_w>=0)
                _text = text_.substring(0,_w) + _conjugate[j][1] + text_.substring(_w+_conjugate[j][0].length(),text_.length());
        }
        return _text;
    }
}