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

public:
    Side *getSides()
    {
        return &sides[SIDES];
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

    // returns whether or not the ball is solved
    bool isSolved()
    {
        Side *currentBall = this->getSides();
        string centerPieceColor;
        string currPieceColor;

        for (int sides = 0; sides < SIDES; sides++)
        {
            // get the color of the center piece
            centerPieceColor = currentBall[sides].getPiece(2, 2).getColor();
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
                        if (currPieceColor != centerPieceColor)
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    // checks if two gearballs are equal (i.e. if both have the same colors in the same faces)
    bool isEqual(Gearball ball)
    {
        Side *currentBall = this->getSides();
        Side *anotherBall = ball.getSides();
        string currPieceColor;
        string anotherPieceColor;

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
                        anotherPieceColor = anotherBall[sides].getPiece(i, j).getColor();
                        if (currPieceColor != anotherPieceColor)
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

        return *this;
    }

    Gearball rotate_rccw()
    {
        for (int i = 0; i < 11; i++)
        {
            this->rotate_rcw();
        }

        return *this;
    }

    Gearball rotate_lcw()
    {
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

        return *this;
    }

    Gearball rotate_lccw()
    {
        for (int i = 0; i < 11; i++)
        {
            this->rotate_lcw();
        }

        return *this;
    }

    Gearball rotate_tcw()
    {
        this->makeCopy();

        // Center Pieces
        for (int colNumber = 0; colNumber < COLUMNS; colNumber++)
        {
            sides[LEFT].setPiece(2, colNumber, previousSides[FRONT].getPiece(2, colNumber));
            sides[FRONT].setPiece(2, colNumber, previousSides[RIGHT].getPiece(2, colNumber));
        }

        sides[RIGHT].setPiece(2, 0, previousSides[REAR].getPiece(2, 4));
        sides[RIGHT].setPiece(2, 1, previousSides[REAR].getPiece(2, 3));
        sides[RIGHT].setPiece(2, 2, previousSides[REAR].getPiece(2, 2));
        sides[RIGHT].setPiece(2, 3, previousSides[REAR].getPiece(2, 1));
        sides[RIGHT].setPiece(2, 4, previousSides[REAR].getPiece(2, 0));

        sides[REAR].setPiece(2, 0, previousSides[LEFT].getPiece(2, 4));
        sides[REAR].setPiece(2, 1, previousSides[LEFT].getPiece(2, 3));
        sides[REAR].setPiece(2, 2, previousSides[LEFT].getPiece(2, 2));
        sides[REAR].setPiece(2, 3, previousSides[LEFT].getPiece(2, 1));
        sides[REAR].setPiece(2, 4, previousSides[LEFT].getPiece(2, 0));

        // Left + Right corners and edges
        for (int colNumber = 0; colNumber < COLUMNS; colNumber++)
        {
            sides[LEFT].setPiece(1, colNumber, previousSides[RIGHT].getPiece(1, colNumber));
            sides[RIGHT].setPiece(1, colNumber, previousSides[LEFT].getPiece(1, colNumber));
        }

        // Front + Rear corners and edges
        sides[FRONT].setPiece(1, 1, previousSides[REAR].getPiece(3, 3));
        sides[FRONT].setPiece(1, 2, previousSides[REAR].getPiece(3, 2));
        sides[FRONT].setPiece(1, 3, previousSides[REAR].getPiece(3, 1));

        sides[REAR].setPiece(3, 3, previousSides[FRONT].getPiece(1, 1));
        sides[REAR].setPiece(3, 2, previousSides[FRONT].getPiece(1, 2));
        sides[REAR].setPiece(3, 1, previousSides[FRONT].getPiece(1, 3));

        // Left + Right Gears
        sides[LEFT].setPiece(0, 2, previousSides[RIGHT].getPiece(0, 2));
        sides[RIGHT].setPiece(0, 2, previousSides[LEFT].getPiece(0, 2));

        // Front + Rear Gears
        sides[FRONT].setPiece(0, 2, previousSides[REAR].getPiece(4, 2));
        sides[REAR].setPiece(4, 2, previousSides[FRONT].getPiece(0, 2));

        // TOP Face Rotation
        this->rotateFace180Deg(TOP);

        return *this;
    }

    Gearball rotate_tccw()
    {
        for (int i = 0; i < 11; i++)
        {
            this->rotate_tcw();
        }

        return *this;
    }

    Gearball rotate_bcw()
    {

        this->makeCopy();

        // Center Pieces
        for (int colNumber = 0; colNumber < COLUMNS; colNumber++)
        {
            sides[LEFT].setPiece(2, colNumber, previousSides[FRONT].getPiece(2, colNumber));
            sides[FRONT].setPiece(2, colNumber, previousSides[RIGHT].getPiece(2, colNumber));
        }

        sides[RIGHT].setPiece(2, 0, previousSides[REAR].getPiece(2, 4));
        sides[RIGHT].setPiece(2, 1, previousSides[REAR].getPiece(2, 3));
        sides[RIGHT].setPiece(2, 2, previousSides[REAR].getPiece(2, 2));
        sides[RIGHT].setPiece(2, 3, previousSides[REAR].getPiece(2, 1));
        sides[RIGHT].setPiece(2, 4, previousSides[REAR].getPiece(2, 0));

        sides[REAR].setPiece(2, 0, previousSides[LEFT].getPiece(2, 4));
        sides[REAR].setPiece(2, 1, previousSides[LEFT].getPiece(2, 3));
        sides[REAR].setPiece(2, 2, previousSides[LEFT].getPiece(2, 2));
        sides[REAR].setPiece(2, 3, previousSides[LEFT].getPiece(2, 1));
        sides[REAR].setPiece(2, 4, previousSides[LEFT].getPiece(2, 0));

        // Left + Right corners, and Edges
        for (int colNumber = 0; colNumber < COLUMNS; colNumber++)
        {
            sides[LEFT].setPiece(3, colNumber, previousSides[RIGHT].getPiece(3, colNumber));
            sides[RIGHT].setPiece(3, colNumber, previousSides[LEFT].getPiece(3, colNumber));
        }

        // Front + Rear corners and edges
        sides[FRONT].setPiece(3, 3, previousSides[REAR].getPiece(1, 1));
        sides[FRONT].setPiece(3, 2, previousSides[REAR].getPiece(1, 2));
        sides[FRONT].setPiece(3, 1, previousSides[REAR].getPiece(1, 3));

        sides[REAR].setPiece(1, 1, previousSides[FRONT].getPiece(3, 3));
        sides[REAR].setPiece(1, 2, previousSides[FRONT].getPiece(3, 2));
        sides[REAR].setPiece(1, 3, previousSides[FRONT].getPiece(3, 1));

        // Left + Right Gears
        sides[LEFT].setPiece(4, 2, previousSides[RIGHT].getPiece(4, 2));
        sides[RIGHT].setPiece(4, 2, previousSides[LEFT].getPiece(4, 2));

        // Front + Rear Gears
        sides[REAR].setPiece(0, 2, previousSides[FRONT].getPiece(4, 2));
        sides[FRONT].setPiece(4, 2, previousSides[REAR].getPiece(0, 2));

        // BOTTOM Face Rotation
        this->rotateFace180Deg(BOTTOM);

        return *this;
    }

    Gearball rotate_bccw()
    {
        for (int i = 0; i < 11; i++)
        {
            this->rotate_bcw();
        }

        return *this;
    }

    // Master rotation function
    Gearball rotate(int moveToPerform, bool print = false)
    {
        switch (moveToPerform)
        {
        case ROTATE_TCW:
            if (print)
                cout << "Rotating the Gearball Top Clockwise: " << endl
                     << endl;
            this->rotate_tcw();
            break;
        case ROTATE_BCW:
            if (print)
                cout << "Rotating the Gearball Bottom Clockwise: " << endl
                     << endl;
            this->rotate_bcw();
            break;
        case ROTATE_LCW:
            if (print)
                cout << "Rotating the Gearball Left Clockwise: " << endl
                     << endl;
            this->rotate_lcw();
            break;
        case ROTATE_RCW:
            if (print)
                cout << "Rotating the Gearball Right Clockwise: " << endl
                     << endl;
            this->rotate_rcw();
            break;
        case ROTATE_TCCW:
            if (print)
                cout << "Rotating the Gearball Top Counter Clockwise: " << endl
                     << endl;
            this->rotate_tccw();
            break;
        case ROTATE_BCCW:
            if (print)
                cout << "Rotating the Gearball Bottom Counter Clockwise: " << endl
                     << endl;
            this->rotate_bccw();
            break;
        case ROTATE_LCCW:
            if (print)
                cout << "Rotating the Gearball Left Counter Clockwise: " << endl
                     << endl;
            this->rotate_lccw();
            break;
        case ROTATE_RCCW:
            if (print)
                cout << "Rotating the Gearball Right Counter Clockwise: " << endl
                     << endl;
            this->rotate_rccw();
            break;
        default:
            cout << "Wrong move input given!" << endl;
            return *this;
        }

        if (print)
        {
            this->printBall();
        }

        return *this;
    }

    // constructor
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
    // to the gearball to come up with a pseudo randomized gearball.
    void randomize(int n, int modular = 8, bool print = false)
    {
        srand(time(0));
        cout << "Running the randomizer function!" << endl;
        cout << "Performing " << n << " total rotation(s) to the gearball: " << endl
             << endl;

        int prevRanRot = -1;
        // n -> the no. of rotations to perform
        for (int i = 0; i < n; i++)
        {

            int ranRot = rand() % modular; // range 0 to 7 - total of 8 different rotation methods

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

            cout << "R" << i + 1 << ". ";
            this->rotate(ranRot, print);
            prevRanRot = ranRot;
        }
    }

    // Overloaded operator for testing the average number of nodes expanded for a k-randomized puzzle
    // to avoid printing unrelevant stuff
    void randomize(int n, string overload, int modular = 8, bool print = false)
    {
        int prevRanRot = -1;
        // n -> the no. of rotations to perform
        for (int i = 0; i < n; i++)
        {

            int ranRot = rand() % modular; // range 0 to 7 - total of 8 different rotation methods

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

            this->rotate(ranRot, print);
            prevRanRot = ranRot;
        }
    }
};

#endif
