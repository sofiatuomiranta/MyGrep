// Sofia Tuomiranta
// MyGrep

#include <algorithm>  // algorithm-kirjasto sis‰lt‰‰ transform-funktion, joka muuttaa merkkijonon kirjaimet pieniksi
#include <iostream>  // iostream-kirjasto sis‰lt‰‰ cin- ja cout-virrat
#include <fstream>  // fstream-kirjasto sis‰lt‰‰ tiedostovirrat
#include <string>  // string-kirjasto sis‰lt‰‰ string-luokan

using namespace std; // K‰ytet‰‰n std-namespacea, jotta ei tarvitse kirjoittaa std::-etuliitett‰ joka kerta

string toLowerCase(const string& str)  // Funktio, joka muuttaa merkkijonon kirjaimet pieniksi
{
	string lower = str;  // Luodaan uusi merkkijono, johon pienet kirjaimet tallennetaan
	transform(lower.begin(), lower.end(), lower.begin(), ::tolower);  // transform-funktiolla muutetaan merkkijonon kirjaimet pieniksi
	return lower;  // Palautetaan pienet kirjaimet sis‰lt‰v‰ merkkijono
}

int main(int argc, char* argv[])  // Ohjelman p‰‰funktio, joka saa argumentteina komentorivilt‰ annetut argumentit
{
	if (argc == 1)  // Jos argumentteja ei ole annettu, pyydet‰‰n k‰ytt‰j‰‰ antamaan lause ja hakusana
	{
		string sana, lause;  // Luodaan muuttujat sana ja lause
		cout << "Anna lause, josta hakutulos etsitaan: ";  // Pyydet‰‰n k‰ytt‰j‰‰ antamaan lause
		getline(cin, lause);  // Luetaan k‰ytt‰j‰n antama lause
		cout << "Anna hakusana, joka yritetaan hakea antamastasi lauseesta: ";  // Pyydet‰‰n k‰ytt‰j‰‰ antamaan hakusana
		getline(cin, sana);  // Luetaan k‰ytt‰j‰n antama hakusana
		string lauseLower = toLowerCase(lause);  // Muutetaan lauseen kirjaimet pieniksi
		string sanaLower = toLowerCase(sana);  // Muutetaan hakusanan kirjaimet pieniksi
		size_t index = lauseLower.find(sanaLower);  // Etsit‰‰n hakusana lauseesta
		if (index != string::npos)  // Jos hakusana lˆytyi lauseesta, tulostetaan lˆytyneen hakusanan indeksi
		{
			cout << "Hakusana loytyi antamastasi lauseesta kohdasta: " << index << endl;  // Tulostetaan lˆytyneen hakusanan indeksi
		}
		else
		{
			cout << "Antamaasi hakusanaa ei loytynyt lauseestasi." << endl;  // Jos hakusanaa ei lˆytynyt lauseesta, tulostetaan virheilmoitus
		}
	}
	else if (argc >= 3)  // Jos argumentteja on annettu, suoritetaan hakutoiminto
	{
		bool l_option = false, o_option = false, i_option = false, r_option = false;  // Luodaan boolean-muuttujat optioille
		string hakusana, tiedostonimi;  // Luodaan muuttujat hakusana ja tiedostonimi
		int argIndex = 1;  // Luodaan muuttuja, joka kertoo, miss‰ argumentissa ollaan
		if (argv[argIndex][0] == '-')  // Jos ensimm‰inen argumentti alkaa v‰liviivalla, se on optio
		{
			string optiot = argv[argIndex];  // Luodaan muuttuja, johon tallennetaan optiot
			for (char optio : optiot)  // K‰yd‰‰n optiot l‰pi
			{
				if (optio == '-') continue;  // Jos optio on v‰liviiva, jatketaan seuraavaan optioon
				if (optio == 'l')  // Jos optio on l, asetetaan l_option trueksi
				{
					l_option = true;  // Asetetaan l_option trueksi
				}
				else if (optio == 'o')  // Jos optio on o, asetetaan o_option trueksi
				{
					o_option = true;  // Asetetaan o_option trueksi
				}
				else if (optio == 'i')  // Jos optio on i, asetetaan i_option trueksi
				{
					i_option = true;  // Asetetaan i_option trueksi
				}
				else if (optio == 'r')  // Jos optio on r, asetetaan r_option trueksi
				{
					r_option = true;  // Asetetaan r_option trueksi
				}
				else
				{
					cerr << "Virhetilanne: Optiota '" << optio << "' ei tunnistettu!" << endl;  // Jos optiota ei tunnistettu, tulostetaan virheilmoitus
					return 1;  // Palautetaan virhekoodi
				}
			}
			argIndex++;  // Siirryt‰‰n seuraavaan argumenttiin
		}
		if (argc > argIndex + 1)  // Jos argumentteja on j‰ljell‰, tallennetaan hakusana ja tiedostonimi
		{
			hakusana = argv[argIndex];  // Tallennetaan hakusana
			tiedostonimi = argv[argIndex + 1];  // Tallennetaan tiedostonimi
		}
		else
		{
			cerr << "Virhetilanne: Hakusana tai tiedostonimi puuttuu!" << endl;  // Jos hakusana tai tiedostonimi puuttuu, tulostetaan virheilmoitus
			return 1;  // Palautetaan virhekoodi
		}
		ifstream tiedosto(tiedostonimi);  // Avataan tiedosto
		if (!tiedosto)  // Jos tiedostoa ei voitu avata, tulostetaan virheilmoitus
		{
			cerr << "Virhetilanne: Tiedostoa '" << tiedostonimi << "' ei voitu avata!" << endl;  // Tulostetaan virheilmoitus
			return 1;  // Palautetaan virhekoodi
		}
		string hakusanaVertailu = i_option ? toLowerCase(hakusana) : hakusana;  // Muutetaan hakusanan kirjaimet pieniksi, jos i_option on true
		string rivi;  // Luodaan muuttuja rivi
		int rivinumero = 0;  // Luodaan muuttuja rivinumero
		int loydetytRivit = 0;  // Luodaan muuttuja loydetytRivit
		while (getline(tiedosto, rivi))  // K‰yd‰‰n tiedosto l‰pi rivi kerrallaan
		{
			rivinumero++;  // Kasvatetaan rivinumeroa
			string vertailtavaRivi = i_option ? toLowerCase(rivi) : rivi;  // Muutetaan rivin kirjaimet pieniksi, jos i_option on true
			bool loytyi = (vertailtavaRivi.find(hakusanaVertailu) != string::npos);  // Tarkistetaan, lˆytyykˆ hakusana rivilt‰
			if ((r_option && !loytyi) || (!r_option && loytyi))  // Jos r_option on true ja hakusanaa ei lˆytynyt rivilt‰ tai r_option on false ja hakusana lˆytyi rivilt‰, tulostetaan rivi
			{
				if (l_option) cout << rivinumero << " -\t";  // Jos l_option on true, tulostetaan rivinumero
				cout << rivi << endl;  // Tulostetaan rivi
				loydetytRivit++;  // Kasvatetaan loydetytRivit-muuttujaa
			}
		}
		if (o_option)  // Jos o_option on true, tulostetaan loydetytRivit-muuttuja
		{
			cout << "Rivien maara, jotka " << (r_option ? "eivat " : "") << "sisall‰ hakusanaa: " << loydetytRivit << endl;  // Tulostetaan loydetytRivit-muuttuja
		}
		tiedosto.close();  // Suljetaan tiedosto
	}
	else
	{
		cerr << "Virhetilanne: Vaara maara argumentteja!" << endl;  // Jos argumentteja on annettu v‰‰r‰ m‰‰r‰, tulostetaan virheilmoitus
		return 1;  // Palautetaan virhekoodi
	}
	return 0;  // Palautetaan 0, eli ohjelma on suoritettu onnistuneesti
}