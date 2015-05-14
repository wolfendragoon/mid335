//CMPS 335
//mid335.cpp
//Bryan Kiggens
//extra credit: with tolerance 0.005 found two bad values
//
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cmath>
using namespace std;

//frequency definitions
#define A4 440.0
#define F0 A4
#define F0_note A
#define F0_octave 4

double testing[108] = {
    16.35,17.32,18.35,
        19.45,        20.6,
        21.83,        23.12,
        24.5,        25.96,
        27.5,        29.14,
        30.87,        32.7,
        34.65,        36.71,
        38.89,        41.2,
        43.65,        46.25,
        49,        51.91,
        55,        58.27,
        61.74,        65.41,
        69.3,        73.42,
        77.78,        82.41,
        87.31,        92.5,
        98,        103.83,
        110,        116.54,
        123.47,        130.81,
        138.59,        146.83,
        155.56,        164.81,
        174.61,        185,
        196,
        207.65,
        220,
        233.08,
        246.94,
        261.63,
        277.18,
        293.66,
        311.13,
        329.63,
        349.23,
        369.99,
        392,
        415.3,
        440,
        466.16,
        493.88,
        523.25,
        554.37,
        587.33,
        622.25,
        659.25,
        698.46,
        739.99,
        783.99,
        830.61,
        880,
        932.33,
        987.77,
        1046.5,
        1108.73,
        1174.66,
        1244.51,
        1318.51,
        1396.91,
        1479.98,
        1567.98,
        1661.22,
        1760,
        1864.66,
        1975.53,
        2093,
        2217.46,
        2349.32,
        2489.02,
        2637.02,
        2793.83,
        2959.96,
        3135.96,
        3322.44,
        3520,
        3729.31,
        3951.07,
        4186.01,
        4434.92,
        4698.63,
        4978.03,
        5274.04,
        5587.65,
        5919.91,
        6271.93,
        6644.88,
        7040,
        7458.62,
        7902.13
};

typedef enum {
	C = 1,
	Cs,
	D,
	Ds,
	E,
	F,
	Fs,
	G,
	Gs,
	A,
	As,
	B,
	END = B,
	HALF_STEPS_PER_OCTAVE = B 
} note_t;

double freq(note_t note, int octave_delta);
void freqtest(double tolerance);


int main(int argc, char *argv[])
{
	note_t note;
	int octave_delta;

	if ((argc != 3)&& (argc != 4)) {
		cout << "Usage: " << argv[0] << " <NOTE>  <OCTAVE_DELTA>" <<"     (optional) tolerance"<< endl;
		return 0;
	}
	//
	note = (note_t)(toupper(argv[1][0]) - 64);
	switch(toupper(argv[1][0])) {
		case 'A': note = A; break;
		case 'B': note = B; break;
		case 'C': note = C; break;
		case 'D': note = D; break;
		case 'E': note = E; break;
		case 'F': note = F; break;
	}
	//You may call your unit test here...
	//cout<<toupper(argv[1][0] - 64)<<endl;
	if(( (toupper(argv[1][0] - 64)) == 26) && (atoi(argv[2]) == 0)){
        if(argc == 4){
        freqtest(atof(argv[3]));
        }
        else{
            cout<<"default freqtest"<<endl;
            freqtest(0.005);
        }
        return 0;

    }else {
        if (note > END) {
		    cout << "Invalid note!" << endl;
		    return 1;
            }
    }
	octave_delta = atoi(argv[2]);
	cout << HALF_STEPS_PER_OCTAVE << endl;
	cout << freq(note, octave_delta) << endl;
	return 0;
}

void freqtest(double tolerance){
    //testing all nine octave
    //
    int tempforec = 0;
    double result = 0;
    note_t notes;
	cout <<"\n tolerance: "<<tolerance <<"\nfreq function unit-test"<< endl;
    cout<<"\nnote octave value    diff\n---- ------ ------- ----------"<<endl;
    for(int j = 0; j <9; j++)

    {
        for(int i = 1; i < 13; i++)//testing for all twelve notes per octave
        {
	        switch(i) {
                case 1: notes = C; break; 
                case 2: notes = Cs; break; 
                case 3: notes = D; break; 
                case 4: notes = Ds; break; 
                case 5: notes = E; break; 
                case 6: notes = F; break; 
                case 7: notes = Fs; break; 
                case 8: notes = G; break; 
                case 9: notes = Gs; break; 
                case 10: notes = A; break; 
                case 11: notes = As; break; 
                case 12: notes = B; break;
            }
            result = freq(notes,j);
            int expectation = i -1 + (j * 12);
            double diffval = result - testing[expectation];
            if(diffval < 0){
                diffval *= -1;
            }
            
            
            cout <<" "<<setw(2)<<i<<"     "<<j<<"    "<<setw(9)<<result<<" "<<setw(11)<<diffval;//endl;
            if(diffval > tolerance){
                cout<<" <----- bad"<<endl;
                tempforec++;
            }else{
                cout<<"    good"<<endl;
            }

            
	    //cout <<"freq:"<<result<<"  expected: "<<testing[expectation]<< endl;
        }


    }
    cout<<"bad element count: "<<tempforec<<"\n unit test complete."<<endl;


}

//-----------------------------------------------------------
//Generate a frequency in hz that is half_steps away from C_4
//Do not modify this function.
//-----------------------------------------------------------
double freq(note_t note, int octave_delta)
{
	double freq;
	double factor;
	double a;
	int n;
	int octave = octave_delta - F0_octave;

	a = pow(2.0, 1.0/(double)HALF_STEPS_PER_OCTAVE);
	n = note - F0_note;
	freq = F0 * pow(a, (double)n);
	factor = pow(2.0, (double)octave);
	freq = freq * factor;
	return freq;
}

