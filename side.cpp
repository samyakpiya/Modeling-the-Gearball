#include "piece.cpp"

const int ROWS = 5;
const int COLUMNS = 5;

class Side
{
private:
    string face; // top, bottom, left, right, front, rear
    Piece pieces[ROWS][COLUMNS];

public:
    // Populate the pieces 2D array with pieces that have the default "X" color and pos value.
    void initialize()
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                this->pieces[i][j] = Piece(" ", " ");
            }
        }
    }

    void generateFace(string color)
    {
        // Creating every piece object that exists for a face
        Piece center = Piece(color, "C");

        Piece corner_tl = Piece(color, "CTL");
        Piece corner_tr = Piece(color, "CTR");
        Piece corner_bl = Piece(color, "CBL");
        Piece corner_br = Piece(color, "CBR");

        Piece edge_t = Piece(color, "ET");
        Piece edge_b = Piece(color, "EB");
        Piece edge_l = Piece(color, "EL");
        Piece edge_r = Piece(color, "ER");

        Piece gear_t = Piece(color, "GT");
        Piece gear_b = Piece(color, "GB");
        Piece gear_l = Piece(color, "GL");
        Piece gear_r = Piece(color, "GR");

        // Placing the pieces in their correct positions in the 2D Array
        pieces[2][2] = center;

        pieces[1][1] = corner_tl;
        pieces[1][3] = corner_tr;
        pieces[3][1] = corner_bl;
        pieces[3][3] = corner_br;

        pieces[1][2] = edge_t;
        pieces[3][2] = edge_b;
        pieces[2][1] = edge_l;
        pieces[2][3] = edge_r;

        pieces[0][2] = gear_t;
        pieces[4][2] = gear_b;
        pieces[2][0] = gear_l;
        pieces[2][4] = gear_r;
    }

    bool putFace(string face)
    {
        string faces("TOP.BOTTOM.LEFT.RIGHT.FRONT.REAR");

        if (faces.find(face) != string::npos) // if face is a valid face type
        {
            this->face = face;
            return true;
        }
        else // if a wrong face value is entered
        {
            this->face = " ";
            cout << "Invalid face entered: " << face << endl;
            return false;
        }
    }

    void printRowColors(int rowNumber)
    {
        cout << "| ";
        for (int colNumber = 0; colNumber < COLUMNS; colNumber++)
        {
            cout << this->pieces[rowNumber][colNumber].getColor() << " | ";
        }
    }

    void printFace()
    {
        for (int i = 0; i < ROWS; i++)
        {
            cout << "| ";
            for (int j = 0; j < COLUMNS; j++)
            {
                cout << this->pieces[i][j].getColor();
                cout << " | ";
            }
            cout << endl;
        }
    }

    void setPiece(int row, int col, Piece piece)
    {
        if (row < ROWS && col < COLUMNS && row >= 0 && col >= 0)
        {
            this->pieces[row][col] = piece;
        }
        else
        {
            cout << "Invalid number of row or column entered: row - " << row << ", col - " << col << endl;
        }
    }

    Piece getPiece(int row, int col)
    {
        // row and col values have to be in range
        return this->pieces[row][col];
    }

    // Note: A side does not have a color, pieces have colors
    Side()
    {
        this->initialize();
        this->face = " ";
    }

    Side(string face, string color)
    {
        this->initialize();
        this->putFace(face);
        this->generateFace(color);
    }
};
