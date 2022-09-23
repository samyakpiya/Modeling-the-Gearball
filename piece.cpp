#include <iostream>
#include <string>
using namespace std;

const string validColors = "RGBYPO";

class Piece
{

private:
    string color;    // Red, Green, Blue, Yellow, Purple, Orange - RGBYPO
    string position; // Acceptable values - l.r.t.b.c.tl.tr.bl.br"

public:
    // check if a color is valid
    bool isValidColor(string color)
    {
        string colors("RGBYPO");

        if (color.length() == 1 || colors.find(color) != string::npos) // if color is valid
        {
            return true;
        }
        else // if color is not valid
        {
            cout << "Invalid color entered: " << color << endl;
            return false;
        }
    }

    // A method that paints a Piece Object to a valid color.
    bool paint(string color)
    {
        if (isValidColor(color))
        {
            this->color = color;
        }
        else
        {
            this->color = " ";
        }
        return isValidColor(color);
    }

    void setColor(string color)
    {
        if (this->isValidColor(color))
        {
            this->color = color;
        }
    }

    // Returns the color of a Piece object
    string getColor()
    {
        return this->color;
    }

    bool putIn(string position)
    {
        string positions("GL.GR.GT.GB.C.CTL.CTR.CBL.CBR.ETL.ETR.EBL.EBR");

        if (positions.find(position) != string::npos) // if pos is valid
        {
            this->position = position;
            return true;
        }
        else
        {
            this->position = " ";
            return false;
        }
    }

    // Returns the position of a Piece object
    string getPosition()
    {
        return this->position;
    }

    // Constructors
    Piece()
    {
        this->color = " ";
        this->position = " ";
    }

    Piece(string color, string position)
    {
        this->paint(color);
        this->putIn(position);
    }
};
