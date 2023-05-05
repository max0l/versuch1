#include <iostream>
#include <b15f/b15f.h>
#include <vector>
#include <cmath>
#include <unistd.h>


int main()
{

	B15F& drv = B15F::getInstance();
	drv.digitalWrite0(0);
	//drv.analogWrite0(1013);
	uint16_t buf[1024];
	const uint16_t count = 1000;
	const uint16_t delta = 1;
	const uint16_t start = 0;
	std::vector<double> primeNumbers = {2,3,5,7,11,13,17,19};

	//Initial value of DAC if set to 1 = 0.007 mV after this its gets incrementet by 0,005 per step

	int i = 0;
    while(1)
    {
    //std::cout<<std::hex<<drv.readDipSwitch()<<std::endl;
		//invertieren
    	if(drv.readDipSwitch() == 1) {
    		std::cout<<"Dip ist 1"<<std::endl;
    		drv.digitalWrite0(~drv.digitalRead0());
    		drv.digitalWrite1(~drv.digitalRead1());//~

		} else if(drv.readDipSwitch() == 2) {
//Night-Rider
		    for(int i2 = 7; i2 >= 0; i2--){
				drv.delay_ms(10);
		        std::cout<< "dg2: " << i2<<std::endl;
				drv.digitalWrite0(pow(2,i2));
		    }
			drv.digitalWrite0(0);

		    for(int j2 = 7; j2 > 0; j2--){
				drv.delay_ms(10);
		        std::cout<< "dg2: " << j2<<std::endl;
				drv.digitalWrite1(pow(2,j2));
		    }
			drv.digitalWrite1(0);


		    for(int j1 = 0; j1<8; j1++){
				drv.delay_ms(10);
		        std::cout<< "dg2: " << j1<<std::endl;
				drv.digitalWrite1(pow(2,j1));
		    }
			drv.digitalWrite1(0);

		    for(int i1 = 0; i1<8; i1++){
				drv.delay_ms(10);
		        std::cout<< "dg1: " << i1<<std::endl;
				drv.digitalWrite0(pow(2,i1));
		    }
			drv.digitalWrite0(0);

			}else if(drv.readDipSwitch() == 3){
			//*5 / 1023 oder 1024
//Reads to voltage? of acd
			double u = drv.analogRead(0);
			std::cout<<u*5/1023<<std::endl;

			
			} else  if(drv.readDipSwitch() == 4) {
//Potis
			double pot1 = drv.analogRead(6);
			double pot2 = drv.analogRead(7);

			std::cout << pot1 << "\t\t" << pot2 <<std::endl;


		} else if(drv.readDipSwitch() == 5) {
//primeNumbers
			std::cout<<"Init"<<std::endl;
			for(double k : primeNumbers){
				std::cout<<k<<std::endl;
				drv.analogWrite0((k/10)*1023/5);
				drv.delay_ms(1500);
			}
			// for(int k = 0; k<100; k++){
			// 	std::cout<<k<<std::endl;
			// 	drv.analogWrite0(k);
			// 	drv.delay_ms(3000);
			//
			// }

		} else if(drv.readDipSwitch() == 6) {
			//DAC
	// 		void B15F::analogSequence 	( 	uint8_t  	channel_a,
	// 			channel_a	Auswahl des ADC a, von 0 - 7
	// 			buffer_a	Speichertort für Werte des Kanals a
	// 			offset_a	Anzahl an Werten des Kanals a, die im Speicher übersprungen werden sollen
	// 			channel_b	Auswahl des ADC b, von 0 - 7
	// 			buffer_b	Speichertort für Werte des Kanals b
	// 			offset_b	Anzahl an Werten des Kanals b, die im Speicher übersprungen werden
	// 			start	Startwert des DACs
	// 			delta	Schrittweite, mit welcher der DAC inkrementiert wird
	// 			count	Anzahl an Inkrementierungen
	// )
			std::cout << "6. Selected" << '\n';
			drv.analogSequence(0, nullptr, 0, 1, nullptr, 0, start, delta, count);
			drv.delay_ms(1000);
		}

    }

}
