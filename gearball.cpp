#ifndef GEARBALL
#define GEARBALL

#include "side.cpp"
#include <stdlib.h> // to use srand() and rand()
#include <time.h>   // to use time for the srand seed

const int SIDES = 6;
const int TOP = 0;
const int BOTTOM = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int FRONT = 4;
const int REAR = 5;

const int ROTATE_TCW = 0;
const int ROTATE_BCW = 1;
const int ROTATE_LCW = 2;
const int ROTATE_RCW = 3;
const int ROTATE_TCCW = 4;
const int ROTATE_BCCW = 5;
const int ROTATE_LCCW = 6;
const int ROTATE_RCCW = 7;

const int ROWSANDCOLS = 5;

class Gearball
{
private:
    Side sides[SIDES];
    Side previousSides[SIDES];
    Side solvedSides[SIDES];

public:
    Gearball getCopy()
    {
        return *this;
    }

    Side *getSides()
    {
        return &sides[SIDES];
    }

    Side *getSolvedSides()
    {
        return &solvedSides[SIDES];
    }

    // for printing the TOP, BOTTOM, and REAR faces in the middle
    void printInMiddle(int middleFace)
    {
        switch (middleFace)
        {
        case TOP:
            cout << string(35, ' ');
            cout << "TOP";
            break;

        case BOTTOM:
            cout << string(35, ' ');
            cout << "BOTTOM";
            break;

        case REAR:
            cout << string(35, ' ');
            cout << "REAR";
            break;
        }

        cout << endl
             << endl;
        for (int rows = 0; rows < COLUMNS; rows++)
        {
            cout << "                           ";
            sides[middleFace].printRowColors(rows);
            cout << endl;
        }

        cout << endl
             << endl
             << endl;
    }

    // for printing the LEFT, FRONT, and RIGHT faces
    void printThreeFaces(int face_a, int face_b, int face_c)
    {
        cout << string(8, ' ');
        cout << "LEFT";

        cout << string(23, ' ');
        cout << "FRONT";

        cout << string(22, ' ');
        cout << "RIGHT";

        cout << endl
             << endl;
        for (int rowNumber = 0; rowNumber < COLUMNS; rowNumber++)
        {
            sides[face_a].printRowColors(rowNumber);
            cout << "     ";
            sides[face_b].printRowColors(rowNumber);
            cout << "     ";
            sides[face_c].printRowColors(rowNumber);
            cout << endl;
        }

        cout << endl
             << endl;
    }

    // for printing the entire gearball
    void printBall()
    {
        this->printInMiddle(TOP);
        this->printThreeFaces(LEFT, FRONT, RIGHT);
        this->printInMiddle(BOTTOM);
        this->printInMiddle(REAR);
    }

    // store a the sorted Gearball sides
    void saveSolvedState()
    {
        this->solvedSides[TOP] = Side("TOP", "Y");
        this->solvedSides[BOTTOM] = Side("BOTTOM", "O");
        this->solvedSides[LEFT] = Side("LEFT", "B");
        this->solvedSides[RIGHT] = Side("RIGHT", "G");
        this->solvedSides[FRONT] = Side("FRONT", "R");
        this->solvedSides[REAR] = Side("REAR", "P");
    }

    void solve()
    {
        this->sides[TOP] = this->solvedSides[TOP];
        this->sides[BOTTOM] = this->solvedSides[BOTTOM];
        this->sides[LEFT] = this->solvedSides[LEFT];
        this->sides[RIGHT] = this->solvedSides[RIGHT];
        this->sides[FRONT] = this->solvedSides[FRONT];
        this->sides[REAR] = this->solvedSides[REAR];
    }

    // returns whether or not the ball is solved
    bool isSolved()
    {
        Side *currentBall = this->getSides();
        string currPieceColor;

        for (int sides = 0; sides < SIDES; sides++)
        {
            for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLUMNS; j++)
                {

                    currPieceColor = currentBall[sides].getPiece(i, j).getColor();
                    if (currPieceColor == " ")
                    {
                        continue;
                    }
                    else
                    {
                        if (sides == TOP && currPieceColor != "Y")
                        {
                            return false;
                        }
                        else if (sides == BOTTOM && currPieceColor != "O")
                        {
                            return false;
                        }
                        else if (sides == LEFT && currPieceColor != "B")
                        {
                            return false;
                        }
                        else if (sides == RIGHT && currPieceColor != "G")
                        {
                            return false;
                        }
                        else if (sides == FRONT && currPieceColor != "R")
                        {
                            return false;
                        }
                        else if (sides == REAR && currPieceColor != "P")
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    // populate the Sides array with every side
    void generateSides()
    {
        this->sides[TOP] = Side("TOP", "Y");
        this->sides[BOTTOM] = Side("BOTTOM", "O");
        this->sides[LEFT] = Side("LEFT", "B");
        this->sides[RIGHT] = Side("RIGHT", "G");
        this->sides[FRONT] = Side("FRONT", "R");
        this->sides[REAR] = Side("REAR", "P");

        this->solvedSides[TOP] = Side("TOP", "Y");
        this->solvedSides[BOTTOM] = Side("BOTTOM", "O");
        this->solvedSides[LEFT] = Side("LEFT", "B");
        this->solvedSides[RIGHT] = Side("RIGHT", "G");
        this->solvedSides[FRONT] = Side("FRONT", "R");
        this->solvedSides[REAR] = Side("REAR", "P");
    }

    void makeCopy()
    {
        this->previousSides[TOP] = this->sides[TOP];
        this->previousSides[BOTTOM] = this->sides[BOTTOM];
        this->previousSides[LEFT] = this->sides[LEFT];
        this->previousSides[RIGHT] = this->sides[RIGHT];
        this->previousSides[FRONT] = this->sides[FRONT];
        this->previousSides[REAR] = this->sides[REAR];
    }

    // Rotation Functions
    void rotateFace90Deg(int side)
    {
        this->makeCopy();
        for (int col = 0; col < ROWSANDCOLS; col++)
        {
            int x = 0;
            for (int row = ROWSANDCOLS - 1; row >= 0; row--)
            {
                // b[colOfMatrix][x] = a[rowOfMatrix][colOfMatrix];
                this->sides[side].setPiece(col, x, this->previousSides[side].getPiece(row, col));
                x++;
            }
        }
    }

    void rotateFace180Deg(int side)
    {
        this->rotateFace90Deg(side);
        this->rotateFace90Deg(side);
    }

    // Right Clockwise
    Gearball rotate_rcw()
    {
        cout << "Rotating the Gearball Right Clockwise: " << endl
             << endl;

        this->makeCopy();

        // Center Pieces
        for (int rowNumber = 0; rowNumber < ROWS; rowNumber++)
        {
            sides[TOP].setPiece(rowNumber, 2, previousSides[FRONT].getPiece(rowNumber, 2));
            sides[FRONT].setPiece(rowNumber, 2, previousSides[BOTTOM].getPiece(rowNumber, 2));
            sides[BOTTOM].setPiece(rowNumber, 2, previousSides[REAR].getPiece(rowNumber, 2));
            sides[REAR].setPiece(rowNumber, 2, previousSides[TOP].getPiece(rowNumber, 2));
        }

        // Corners, and Edges
        for (int rowNumber = 0; rowNumber < ROWS; rowNumber++)
        {
            sides[TOP].setPiece(rowNumber, 3, previousSides[BOTTOM].getPiece(rowNumber, 3));
            sides[FRONT].setPiece(rowNumber, 3, previousSides[REAR].getPiece(rowNumber, 3));
            sides[BOTTOM].setPiece(rowNumber, 3, previousSides[TOP].getPiece(rowNumber, 3));
            sides[REAR].setPiece(rowNumber, 3, previousSides[FRONT].getPiece(rowNumber, 3));
        }

        // Gears
        sides[TOP].setPiece(2, 4, previousSides[BOTTOM].getPiece(2, 4));
        sides[FRONT].setPiece(2, 4, previousSides[REAR].getPiece(2, 4));
        sides[BOTTOM].setPiece(2, 4, previousSides[TOP].getPiece(2, 4));
        sides[REAR].setPiece(2, 4, previousSides[FRONT].getPiece(2, 4));

        // Right Face Rotation
        this->rotateFace180Deg(RIGHT);

        printBall();

        return *this;
    }

    Gearball rotate_rccw()
    {
        cout << "Rotating the Gearball Right Counter Clockwise: " << endl
             << endl;

        this->makeCopy();

        // Center Pieces
        for (int rowNumber = 0; rowNumber < ROWS; rowNumber++)
        {
            sides[TOP].setPiece(rowNumber, 2, previousSides[REAR].getPiece(rowNumber, 2));
            sides[FRONT].setPiece(rowNumber, 2, previousSides[TOP].getPiece(rowNumber, 2));
            sides[BOTTOM].setPiece(rowNumber, 2, previousSides[FRONT].getPiece(rowNumber, 2));
            sides[REAR].setPiece(rowNumber, 2, previousSides[BOTTOM].getPiece(rowNumber, 2));
        }

        // Corners, and Edges
        for (int rowNumber = 0; rowNumber < ROWS; rowNumber++)
        {
            sides[TOP].setPiece(rowNumber, 3, previousSides[BOTTOM].getPiece(rowNumber, 3));
            sides[FRONT].setPiece(rowNumber, 3, previousSides[REAR].getPiece(rowNumber, 3));
            sides[BOTTOM].setPiece(rowNumber, 3, previousSides[TOP].getPiece(rowNumber, 3));
            sides[REAR].setPiece(rowNumber, 3, previousSides[FRONT].getPiece(rowNumber, 3));
        }

        // Gears
        sides[TOP].setPiece(2, 4, previousSides[BOTTOM].getPiece(2, 4));
        sides[FRONT].setPiece(2, 4, previousSides[REAR].getPiece(2, 4));
        sides[BOTTOM].setPiece(2, 4, previousSides[TOP].getPiece(2, 4));
        sides[REAR].setPiece(2, 4, previousSides[FRONT].getPiece(2, 4));

        // Right Face Rotation
        this->rotateFace180Deg(RIGHT);

        printBall();

        return *this;
    }

    Gearball rotate_lcw()
    {
        cout << "Rotating the Gearball Left Clockwise: " << endl
             << endl;

        this->makeCopy();

        // Center Pieces
        for (int rowNumber = 0; rowNumber < ROWS; rowNumber++)
        {
            sides[TOP].setPiece(rowNumber, 2, previousSides[FRONT].getPiece(rowNumber, 2));
            sides[FRONT].setPiece(rowNumber, 2, previousSides[BOTTOM].getPiece(rowNumber, 2));
            sides[BOTTOM].setPiece(rowNumber, 2, previousSides[REAR].getPiece(rowNumber, 2));
            sides[REAR].setPiece(rowNumber, 2, previousSides[TOP].getPiece(rowNumber, 2));
        }

        // Corners, and Edges
        for (int rowNumber = 0; rowNumber < ROWS; rowNumber++)
        {
            sides[TOP].setPiece(rowNumber, 1, previousSides[BOTTOM].getPiece(rowNumber, 1));
            sides[FRONT].setPiece(rowNumber, 1, previousSides[REAR].getPiece(rowNumber, 1));
            sides[BOTTOM].setPiece(rowNumber, 1, previousSides[TOP].getPiece(rowNumber, 1));
            sides[REAR].setPiece(rowNumber, 1, previousSides[FRONT].getPiece(rowNumber, 1));
        }

        // Gears
        sides[TOP].setPiece(2, 0, previousSides[BOTTOM].getPiece(2, 0));
        sides[FRONT].setPiece(2, 0, previousSides[REAR].getPiece(2, 0));
        sides[BOTTOM].setPiece(2, 0, previousSides[TOP].getPiece(2, 0));
        sides[REAR].setPiece(2, 0, previousSides[FRONT].getPiece(2, 0));

        // Left Face Rotation
        this->rotateFace180Deg(LEFT);

        printBall();

        return *this;
    }

    Gearball rotate_lccw()
    {
        cout << "Rotating the Gearball Left Counter Clockwise: " << endl
             << endl;

        this->makeCopy();

        // Center Pieces
        for (int rowNumber = 0; rowNumber < ROWS; rowNumber++)
        {
            sides[TOP].setPiece(rowNumber, 2, previousSides[REAR].getPiece(rowNumber, 2));
            sides[FRONT].setPiece(rowNumber, 2, previousSides[TOP].getPiece(rowNumber, 2));
            sides[BOTTOM].setPiece(rowNumber, 2, previousSides[FRONT].getPiece(rowNumber, 2));
            sides[REAR].setPiece(rowNumber, 2, previousSides[BOTTOM].getPiece(rowNumber, 2));
        }

        // Corners, and Edges
        for (int rowNumber = 0; rowNumber < ROWS; rowNumber++)
        {
            sides[TOP].setPiece(rowNumber, 1, previousSides[BOTTOM].getPiece(rowNumber, 1));
            sides[FRONT].setPiece(rowNumber, 1, previousSides[REAR].getPiece(rowNumber, 1));
            sides[BOTTOM].setPiece(rowNumber, 1, previousSides[TOP].getPiece(rowNumber, 1));
            sides[REAR].setPiece(rowNumber, 1, previousSides[FRONT].getPiece(rowNumber, 1));
        }

        // Gears
        sides[TOP].setPiece(2, 0, previousSides[BOTTOM].getPiece(2, 0));
        sides[FRONT].setPiece(2, 0, previousSides[REAR].getPiece(2, 0));
        sides[BOTTOM].setPiece(2, 0, previousSides[TOP].getPiece(2, 0));
        sides[REAR].setPiece(2, 0, previousSides[FRONT].getPiece(2, 0));

        // Left Face Rotation
        this->rotateFace180Deg(LEFT);

        printBall();

        return *this;
    }

    Gearball rotate_tcw()
    {
        cout << "Rotating the Gearball Top Clockwise: " << endl
             << endl;

        this->makeCopy();

        // Center Pieces
        for (int colNumber = 0; colNumber < COLUMNS; colNumber++)
        {
            sides[LEFT].setPiece(2, colNumber, previousSides[FRONT].getPiece(2, colNumber));
            sides[FRONT].setPiece(2, colNumber, previousSides[RIGHT].getPiece(2, colNumber));
            sides[RIGHT].setPiece(2, colNumber, previousSides[REAR].getPiece(2, colNumber));
            sides[REAR].setPiece(2, colNumber, previousSides[LEFT].getPiece(2, colNumber));
        }

        // Corners, and Edges
        for (int colNumber = 0; colNumber < COLUMNS; colNumber++)
        {
            sides[LEFT].setPiece(1, colNumber, previousSides[RIGHT].getPiece(1, colNumber));
            sides[FRONT].setPiece(1, colNumber, previousSides[REAR].getPiece(1, colNumber));
            sides[RIGHT].setPiece(1, colNumber, previousSides[LEFT].getPiece(1, colNumber));
            sides[REAR].setPiece(3, colNumber, previousSides[FRONT].getPiece(3, colNumber));
        }

        // Gears
        sides[LEFT].setPiece(0, 2, previousSides[RIGHT].getPiece(0, 2));
        sides[FRONT].setPiece(0, 2, previousSides[REAR].getPiece(0, 2));
        sides[RIGHT].setPiece(0, 2, previousSides[LEFT].getPiece(0, 2));
        sides[REAR].setPiece(4, 2, previousSides[FRONT].getPiece(4, 2));

        // TOP Face Rotation
        this->rotateFace180Deg(TOP);

        printBall();

        return *this;
    }

    Gearball rotate_tccw()
    {
        cout << "Rotating the Gearball Top Counter Clockwise: " << endl
             << endl;

        this->makeCopy();

        // Center Pieces
        for (int colNumber = 0; colNumber < COLUMNS; colNumber++)
        {
            sides[LEFT].setPiece(2, colNumber, previousSides[REAR].getPiece(2, 4 - colNumber));
            sides[FRONT].setPiece(2, colNumber, previousSides[LEFT].getPiece(2, colNumber));
            sides[RIGHT].setPiece(2, colNumber, previousSides[FRONT].getPiece(2, colNumber));
            sides[REAR].setPiece(2, colNumber, previousSides[RIGHT].getPiece(2, colNumber));
        }

        // Corners, and Edges
        for (int colNumber = 0; colNumber < COLUMNS; colNumber++)
        {
            sides[LEFT].setPiece(1, colNumber, previousSides[RIGHT].getPiece(1, colNumber));
            sides[FRONT].setPiece(1, colNumber, previousSides[REAR].getPiece(3, 4 - colNumber));
            sides[RIGHT].setPiece(1, colNumber, previousSides[LEFT].getPiece(1, colNumber));
            sides[REAR].setPiece(3, colNumber, previousSides[FRONT].getPiece(1, 4 - colNumber));
        }

        // Gears
        sides[LEFT].setPiece(0, 2, previousSides[RIGHT].getPiece(0, 2));
        sides[FRONT].setPiece(0, 2, previousSides[REAR].getPiece(0, 2));
        sides[RIGHT].setPiece(0, 2, previousSides[LEFT].getPiece(0, 2));
        sides[REAR].setPiece(4, 2, previousSides[FRONT].getPiece(4, 2));

        // TOP Face Rotation
        this->rotateFace180Deg(TOP);

        printBall();

        return *this;
    }

    Gearball rotate_bcw()
    {
        cout << "Rotating the Gearball Bottom Clockwise: " << endl
             << endl;

        this->makeCopy();

        // Center Pieces
        for (int colNumber = 0; colNumber < COLUMNS; colNumber++)
        {
            sides[LEFT].setPiece(2, colNumber, previousSides[FRONT].getPiece(2, colNumber));
            sides[FRONT].setPiece(2, colNumber, previousSides[RIGHT].getPiece(2, colNumber));
            sides[RIGHT].setPiece(2, colNumber, previousSides[REAR].getPiece(2, colNumber));
            sides[REAR].setPiece(2, colNumber, previousSides[LEFT].getPiece(2, colNumber));
        }

        // Corners, and Edges
        for (int colNumber = 0; colNumber < COLUMNS; colNumber++)
        {
            sides[LEFT].setPiece(3, colNumber, previousSides[RIGHT].getPiece(3, colNumber));
            sides[FRONT].setPiece(3, colNumber, previousSides[REAR].getPiece(1, colNumber));
            sides[RIGHT].setPiece(3, colNumber, previousSides[LEFT].getPiece(3, colNumber));
            sides[REAR].setPiece(1, colNumber, previousSides[FRONT].getPiece(3, colNumber));
        }

        // Gears
        sides[LEFT].setPiece(4, 2, previousSides[RIGHT].getPiece(4, 2));
        sides[FRONT].setPiece(4, 2, previousSides[REAR].getPiece(0, 2));
        sides[RIGHT].setPiece(4, 2, previousSides[LEFT].getPiece(4, 2));
        sides[REAR].setPiece(0, 2, previousSides[FRONT].getPiece(4, 2));

        // BOTTOM Face Rotation
        this->rotateFace180Deg(BOTTOM);

        printBall();

        return *this;
    }

    Gearball rotate_bccw()
    {
        cout << "Rotating the Gearball Bottom Counter Clockwise: " << endl
             << endl;

        this->makeCopy();

        // Center Pieces
        for (int colNumber = 0; colNumber < COLUMNS; colNumber++)
        {
            sides[LEFT].setPiece(2, colNumber, previousSides[REAR].getPiece(2, colNumber));
            sides[FRONT].setPiece(2, colNumber, previousSides[LEFT].getPiece(2, colNumber));
            sides[RIGHT].setPiece(2, colNumber, previousSides[FRONT].getPiece(2, colNumber));
            sides[REAR].setPiece(2, colNumber, previousSides[RIGHT].getPiece(2, colNumber));
        }

        // Corners, and Edges
        for (int colNumber = 0; colNumber < COLUMNS; colNumber++)
        {
            sides[LEFT].setPiece(3, colNumber, previousSides[RIGHT].getPiece(3, colNumber));
            sides[FRONT].setPiece(3, colNumber, previousSides[REAR].getPiece(1, colNumber));
            sides[RIGHT].setPiece(3, colNumber, previousSides[LEFT].getPiece(3, colNumber));
            sides[REAR].setPiece(1, colNumber, previousSides[FRONT].getPiece(3, colNumber));
        }

        // Gears
        sides[LEFT].setPiece(4, 2, previousSides[RIGHT].getPiece(4, 2));
        sides[FRONT].setPiece(4, 2, previousSides[REAR].getPiece(0, 2));
        sides[RIGHT].setPiece(4, 2, previousSides[LEFT].getPiece(4, 2));
        sides[REAR].setPiece(0, 2, previousSides[FRONT].getPiece(4, 2));

        // TOP Face Rotation
        this->rotateFace180Deg(BOTTOM);

        printBall();

        return *this;
    }

    Gearball rotate(int moveToPerform)
    {
        switch (moveToPerform)
        {
        case ROTATE_TCW:
            return this->rotate_tcw();
        case ROTATE_BCW:
            return this->rotate_bcw();
        case ROTATE_LCW:
            return this->rotate_lcw();
        case ROTATE_RCW:
            return this->rotate_rcw();
        case ROTATE_TCCW:
            return this->rotate_tccw();
        case ROTATE_BCCW:
            return this->rotate_bccw();
        case ROTATE_LCCW:
            return this->rotate_lccw();
        case ROTATE_RCCW:
            return this->rotate_rccw();
        default:
            cout << "Wrong move input given!" << endl;
            return *this;
        }
    }

    Gearball()
    {
        this->generateSides();
    }

    // function to avoid consequent clockwise and counterclockwise rotations that negate rotation effects
    int restartRandomization(int ranNumToAvoid)
    {
        srand(time(0));
        int ranRot = rand() % 8;
        while (ranRot == ranNumToAvoid)
        {
            ranRot = rand() % 8;
        }
        return ranRot;
    }

    // random rotation functions - picks rotation functions and applies them
    // to the gearball to come up with a randomized gearball.
    void randomize(int n)
    {
        srand(time(0));
        cout << "Running the randomizer function!" << endl;
        cout << "Performing " << n << " total rotations to the gearball: " << endl
             << endl;

        int prevRanRot = -1;
        // n -> the no. of rotations to perform
        for (int i = 0; i < n; i++)
        {

            int ranRot = rand() % 8; // range 0 to 7 - total of 8 different rotation methods

            // to avoid a sequence of clockwise and counter clockwise rotations
            // (for example, top clockwise and then top counterclockwise which negates one another)
            if (prevRanRot == ROTATE_TCW && ranRot == ROTATE_TCCW)
            {
                ranRot = restartRandomization(ranRot);
            }
            else if (prevRanRot == ROTATE_TCCW && ranRot == ROTATE_TCW)
            {
                ranRot = restartRandomization(ranRot);
            }
            else if (prevRanRot == ROTATE_BCW && ranRot == ROTATE_BCCW)
            {
                ranRot = restartRandomization(ranRot);
            }
            else if (prevRanRot == ROTATE_BCCW && ranRot == ROTATE_BCW)
            {
                ranRot = restartRandomization(ranRot);
            }
            else if (prevRanRot == ROTATE_LCW && ranRot == ROTATE_LCCW)
            {
                ranRot = restartRandomization(ranRot);
            }
            else if (prevRanRot == ROTATE_LCCW && ranRot == ROTATE_LCW)
            {
                ranRot = restartRandomization(ranRot);
            }
            else if (prevRanRot == ROTATE_RCW && ranRot == ROTATE_RCCW)
            {
                ranRot = restartRandomization(ranRot);
            }
            else if (prevRanRot == ROTATE_RCCW && ranRot == ROTATE_RCW)
            {
                ranRot = restartRandomization(ranRot);
            }

            cout << i + 1 << ". "; // Indexing each rotation performed

            this->rotate(ranRot);
            prevRanRot = ranRot;
        }
    }

    void randomizeCC(int n)
    {
        srand(time(0));
        cout << "Running the clockwise randomizer function!" << endl;
        cout << "Performing " << n << " total clockwise rotations to the gearball: " << endl
             << endl;

        int ranRot;
        int prevRanRot = -1;
        for (int i = 0; i < n; i++)
        {
            ranRot = rand() % 4;
            while (ranRot == prevRanRot)
            {
                ranRot = rand() % 4;
            }

            this->rotate(ranRot);
            prevRanRot = ranRot;
        }
    }
};

#endif
