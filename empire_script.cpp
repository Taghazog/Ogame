#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;

const int nbLine = 592;
string str[nbLine];
string bbcode = "";
size_t nb_planets = 1;

string index_string;          // string which will contain the result

ostringstream convert;   // stream used for the conversion

void testparser(string filename)
{
	string line;
	ifstream in(filename.c_str());
	ofstream out("empire_out.txt");

	int i = 0;
	if (in.is_open())
	{
		string token;
    	stringstream iss;
    	while ( getline(in, line) )
    	{
        	iss << line;
        	while ( getline(iss, token, ' ') )
        	{
            	if( !token.empty() )
				{
					out << token << endl;
					++i;
				}
				token = "";
        	}
        	line = "";
        	iss.clear();
    	}

		in.close();
	}

	else
	{
		cout << "Unable to open file" << endl;
		exit(EXIT_FAILURE);
	}
}

void openfile(string filename)
{
	string line;
	ifstream in(filename.c_str());

	int i = 0;
	if (in.is_open())
	{
		string token;
    	stringstream iss;
    	while ( getline(in, line) )
    	{
        	iss << line;
        	while ( getline(iss, token, ' ') )
        	{
            	if( !token.empty() )
				{
					str[i] = token;
					++i;
				}
				token = "";
        	}
        	line = "";
        	iss.clear();
    	}

		in.close();
	}

	else
	{
		cout << "Unable to open file" << endl;
		exit(EXIT_FAILURE);
	}

}

//str[101] pour le nombre de planete
void check_nb_planets()
{
	nb_planets = count(str[77].begin(), str[77].end(), '|') - 1;
}

void per_planet_values(string *out, const string in)
{
	stringstream entireline, caseline;
	string cases, numbers;
	entireline << in;
	int i = 0;
	convert.clear();
	convert.str("");

	while(getline(entireline, cases, '|'))
	{
		caseline << cases;
		while(getline(caseline, numbers, '_'))
		{
			if(!numbers.empty())
			{
				convert.str(convert.str() + numbers);
			}
		}
		if(!cases.empty())
		{
			out[i] = convert.str();
			++i;
		}
		numbers = "";
		caseline.clear();
		convert.clear();
		convert.str("");
	}
	entireline.clear();
}

void compute_prod(stringstream& prod, string& prod_heure, string& prod_semaine)
{
	int value = 0;
	int tmp_value = 0;
	string tmp;
	stringstream tmp_stream;

	while(getline(prod, tmp, '.'))
	{
		tmp_stream << tmp;
		tmp_stream >> tmp_value;
		value = value * 1000 + tmp_value;
		tmp_stream.clear();
		tmp_stream.str("");
	}



	tmp_stream << (int) value/24;
	tmp_stream >> tmp;
	tmp_value = 1;
	tmp_stream.clear();
	tmp_stream.str("");
	for(reverse_iterator<string::iterator> r = tmp.rbegin(); r < tmp.rend(); ++r)
	{
		if((tmp_value-1)%3 == 0 && tmp_value != 1)
		{
			tmp_stream.str("." + tmp_stream.str());
		}
		tmp_stream.str(*r + tmp_stream.str());

		++tmp_value;
	}

	prod_heure = tmp_stream.str();
	tmp_stream.clear();
	tmp_stream.str("");

	tmp_stream << value * 7;
	tmp_stream >> tmp;
	tmp_value = 1;
	tmp_stream.clear();
	tmp_stream.str("");
	for(reverse_iterator<string::iterator> r = tmp.rbegin(); r < tmp.rend(); ++r)
	{
		if((tmp_value-1)%3 == 0 && tmp_value != 1)
		{
			tmp_stream.str("." + tmp_stream.str());
		}
		tmp_stream.str(*r + tmp_stream.str());

		++tmp_value;
	}

	prod_semaine = tmp_stream.str();

}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////
void title()
{
	bbcode = bbcode + "[center][color=orange][b]" + str[4] + " - Univers Orion[/b]\n[i]Mis à jour le " + str[9] + " " + str[10] + " " + str[11] + "[/i]\n\n\n";
}

void classement()
{
	bbcode = bbcode + "[table border=4 align = center] [tr] [td] [center]Categorie[/center] [/td][td][img]http://s6.postimage.org/odyp9hqi5/iconpoints.png[/img] [/td][td] [img]http://s6.postimage.org/c9o1692zx/iconeconomie.png[/img]  [/td][td] [img]http://s6.postimage.org/jtciuk6st/iconrecherche.png[/img] [/td][td]  [img]http://s6.postimage.org/bqnjaq0z1/iconmilitaire.png[/img] [/td] [/tr][tr] [td] [center] Classement [/center] [/td][td] [center]TODO[/center] [/td][td] [center]TODO[/center] [/td][td] [center]TODO[/center] [/td][td] [center]TODO[/center] [/td] [/tr] [/table]\n\n";
}

void points()
{

	bbcode = bbcode + "[img]http://s6.postimage.org/hjeplepo1/pointsio.png[/img]\n\n[table border=4 align = center style=width:50%;][tr][td][center]Mines[/center][/td][td][right]" + str[20] + "[/right][/td] [td][center]" + str[22] + "% [/center][/td][/tr][tr][td][center]Batiments[/center][/td][td][right]" + str[29] + "[/right][/td] [td][center]" + str[31] + "%[/center][/td][/tr][tr][td][center]Défense[/center][/td][td][right]" + str[37] + "[/right][/td][td][center]" + str[39] + "%[/center][/td][/tr][tr][td][right][center]Recherche[/center][/right][/td][td][right]" + str[45] + "[/right][/td][td][center]" + str[47] + "%[/center][/td][/tr][tr][td][right][center]Flotte[/center][/right][/td][td][right]" + str[53] + "[/right][/td][td][center]" + str[55] + "%[/center][/td][/tr][tr][td][right][center]Total[/center][/right][/td][td][right]" + str[60] + "[/right][/td][td][center]" + str[63] + "\nInd.[/center][/td][/tr][/table]";
}

void production()
{
	/*
	69 		production metal/jour
	72 		production cristal/jour
	75 		production deut/jour
	*/

	string metal_heure;
	string cristal_heure;
	string deut_heure;
	string metal_semaine;
	string cristal_semaine;
	string deut_semaine;

	stringstream prod;

	prod << str[69];
	compute_prod(prod, metal_heure, metal_semaine);
	prod.clear();

	prod << str[72];
	compute_prod(prod, cristal_heure, cristal_semaine);
	prod.clear();

	prod << str[75];
	compute_prod(prod, deut_heure, deut_semaine);
	prod.clear();

	bbcode = bbcode + "[img]http://s6.postimage.org/jmp4t2pgx/productionn.png[/img]\n\n[table border=4 align = center style=width:50%;] [tr][td] Ressources/\nProduction [/td] [td][right][img]http://s6.postimage.org/k7n1ln5nx/iconmetal.png[/img][/right][/td] [td][right][img]http://s6.postimage.org/t8wzlie7h/iconcrystal.png[/img][/right][/td] [td][right][img]http://s6.postimage.org/h37sb3zhp/icondeuterium.png[/img][/right][/td] [/tr][tr] [td] Prod/Heure [/td] [td][right]" + metal_heure + "[/right][/td] [td][right]" + cristal_heure + "[/right][/td] [td][right]" + deut_heure + "[/right][/td] [/tr][tr] [td] Prod/Jour [/td] [td][right]" + str[69] + "[/right][/td] [td][right]" + str[72] + "[/right][/td] [td][right]" + str[75] + "[/right][/td] [/tr][tr] [td] Prod/Semaine [/td] [td][right]" + metal_semaine + "[/right][/td] [td][right]" + cristal_semaine + "[/right][/td] [td][right]" + deut_semaine + "[/right][/td] [/tr] [/table]";
}

void ressources()
{
	bbcode = bbcode + "[img]http://s6.postimage.org/5ezg4fcs1/ressourcesi.png[/img]\n\n[table border=4 align = center] [tr] [td] [center] Batiment/\n Coordonnées [/center] [/td] [td][center][img]http://s6.postimage.org/qxuc3le25/minemetal.png[/img]\n Met.[/center] [/td][td][center][img]http://s6.postimage.org/89cag9n59/minecrystal.png[/img]\n Cr.[/center] [/td][td][center][img]http://s6.postimage.org/ngsa0mezx/minedeuterium.png[/img]\n Deut.[/center] [/td][td][center][img]http://s6.postimage.org/r96ovpbot/solarenergy.png[/img]\n CES[/center] [/td][td][center][img]http://s6.postimage.org/6s97nobxp/fusionenergy.png[/img]\n CEF[/center] [/td][td][center][img]http://s6.postimage.org/86rwmiq25/satsenergy.png[/img]\n Sats[/center] [/td][td][center][img]http://s6.postimage.org/wm58887sd/hangarmetal.png[/img]\n Hangar M.[/center] [/td][td][center][img]http://s6.postimage.org/67kzti3xp/hangarcrystall.png[/img]\n Hangar C.[/center] [/td][td][center][img]http://s6.postimage.org/iv5cjr88d/hangardeuteriuml.png[/img]\n Hangar D.[/center] [/td] [/tr]";

	/*
	94 		Mine Metal
	102		Mine Cristal
	110		Mine Deuterium
	171		CES
	162		CEF
	179		Sats
	119 	Hangar M.
	127		Hangar C.
	135 	Hangar D.
	*/

	string metal[nb_planets];
	string cristal[nb_planets];
	string deut[nb_planets];
	string ces[nb_planets];
	string cef[nb_planets];
	string sats[nb_planets];
	string hang_metal[nb_planets];
	string hang_cristal[nb_planets];
	string hang_deut[nb_planets];

	per_planet_values(metal, 		str[94 ]);
	per_planet_values(cristal, 		str[102]);
	per_planet_values(deut, 		str[110]);
	per_planet_values(ces, 			str[171]);
	per_planet_values(cef, 			str[162]);
	per_planet_values(sats, 		str[179]);
	per_planet_values(hang_metal, 	str[119]);
	per_planet_values(hang_cristal,	str[127]);
	per_planet_values(hang_deut, 	str[135]);

	 for(int i = 0; i < nb_planets; ++i)
	 {
	 	convert << i + 1;

		index_string = convert.str();

		bbcode = bbcode + "[tr] [td] [center]Planete " + index_string + "\ncoordonnees[/center] [/td][td][center]" + metal[i] + "[/center] [/td][td][center]" + cristal[i] + "[/center] [/td][td][center]" + deut[i] + "[/center] [/td][td][center]" + ces[i] + "[/center] [/td][td][center]" + cef[i] + "[/center] [/td][td][center]" + sats[i] + "[/center] [/td][td][center]" + hang_metal[i] + "[/center] [/td][td][center]" + hang_cristal[i] + "[/center] [/td][td][center]" + hang_deut[i] + "[/center] [/td] [/tr]";

		convert.str("");
	}

	bbcode = bbcode + "[/table]";

}

void installations()
{
	bbcode = bbcode + "[img]http://s6.postimage.org/au865e4c1/installations.png[/img]\n\n[table border=4 align = center] [tr] [td] [center] Batiment/\n Coordonnées [/center] [/td][td][center][img]http://s6.postimage.org/9yldoc2ul/robotsq.png[/img]\n Robots[/center] [/td][td][center][img]http://s6.postimage.org/gu0imsei5/spatial.png[/img]\n Chantier[/center] [/td][td][center][img]http://s6.postimage.org/mv2sxlqi5/nanite.png[/img]\n Nanite[/center] [/td][td][center][img]http://s6.postimage.org/9w63f8okt/laboy.png[/img]\n Labo[/center] [/td][td][center][img]http://s6.postimage.org/l1zw9a5bh/missilesilo.png[/img]\n Silo[/center] [/td][td][center][img]http://s6.postimage.org/cm5qe1d2l/ravitaillement.png[/img]\n Depot[/center] [/td][td][center][img]http://s6.postimage.org/64mtuj2p9/terraformeur.png[/img]\n Terra.[/center] [/td] [/tr]";

	/*
	187		Robots
	210		Chantier
	195		Nanite
	234		Labos
	225		Silo
	217		Depot
	203		Terraformeur
	*/

	string robots[nb_planets];
	string chantier[nb_planets];
	string nanite[nb_planets];
	string labo[nb_planets];
	string silo[nb_planets];
	string depot[nb_planets];
	string terra[nb_planets];


	per_planet_values(robots, 		str[187]);
	per_planet_values(chantier, 	str[210]);
	per_planet_values(nanite, 		str[195]);
	per_planet_values(labo, 		str[234]);
	per_planet_values(silo, 		str[225]);
	per_planet_values(depot, 		str[217]);
	per_planet_values(terra, 		str[203]);


	for(int i = 0; i < nb_planets; ++i)
 	{
	 	convert << i + 1;

		index_string = convert.str();

		bbcode = bbcode + "[tr] [td] [center]Planete " + index_string + "\ncoordonnees[/center] [/td][td][center]" + robots[i] + "[/center] [/td][td][center]" + chantier[i] + "[/center] [/td][td][center]" + nanite[i] + "[/center] [/td][td][center]" + labo[i] + "[/center] [/td][td][center]" + silo[i] + "[/center] [/td][td][center]" + depot[i] + "[/center] [/td][td][center]" + terra[i] + "[/center] [/td] [/tr]";

		convert.str("");
	}

 	bbcode = bbcode + "[/table]";
}

void defenses()
{
	bbcode = bbcode + "[img]http://s6.postimage.org/8qxqxq4j5/defenses.png[/img]\n\n[table border=4 align = center][tr][td] [center] Défense/ \n Coordonnées [/center] [/td][td][center][img]http://s6.postimage.org/6y4j7srjh/29224789.png[/img]\n Lm[/center] [/td][td][center][img]http://s6.postimage.org/je191jkvh/50799087.png[/img]\n L.leger[/center] [/td][td][center][img]http://s6.postimage.org/vdcr8uqgd/62862056.png[/img]\n L.lourd[/center] [/td][td][center][img]http://s6.postimage.org/6qz9u9a3x/gaussk.png[/img]\n Gauss[/center] [/td][td][center][img]http://s6.postimage.org/9d105yx65/ioncanon.png[/img]\n Ions[/center] [/td][td][center][img]http://s6.postimage.org/bccicq8od/plasmacanon.png[/img]\n Plasma[/center] [/td] [/tr]";

	/*
	439		lm
	447		ll
	455		Llo
	471 	Gauss
	463		Ions
	479		Plasma
	*/

	string lm[nb_planets];
	string ll[nb_planets];
	string llo[nb_planets];
	string gauss[nb_planets];
	string ions[nb_planets];
	string plasma[nb_planets];

	per_planet_values(lm, 		str[439]);
	per_planet_values(ll, 		str[447]);
	per_planet_values(llo, 		str[455]);
	per_planet_values(gauss, 	str[471]);
	per_planet_values(ions, 	str[463]);
	per_planet_values(plasma, 	str[479]);


	for(int i = 0; i < nb_planets; ++i)
	{
		convert << i + 1;

		index_string = convert.str();

		bbcode = bbcode + "[tr] [td] [center]Planete " + index_string + "\ncoordonnees[/center] [/td][td][center]" + lm[i] + "[/center] [/td][td][center]" + ll[i] + "[/center] [/td][td][center]" + llo[i] + "[/center] [/td][td][center]" + gauss[i] + "[/center] [/td][td][center]" + ions[i] + "[/center] [/td][td][center]" + plasma[i] + "[/center] [/td] [/tr]";

		convert.str("");
	}

	bbcode = bbcode + "[/table]";


	bbcode = bbcode + "[table border=4 align = center] [tr] [td] [center] Défense/\n Coordonnées [/center] [/td][td][center][img]http://s6.postimage.org/wuxpdi1rh/petiti.png[/img]\n Petit B.[/center] [/td][td][center][img]http://s6.postimage.org/f7u6rfpf1/grand.png[/img]\n Grand B.[/center] [/td][td][center][img]http://s6.postimage.org/kchm3ty7h/99370312.png[/img]\n Mi[/center] [/td][td][center][img]http://s6.postimage.org/okbw5o67h/mipp.png[/img]\n MIP[/center] [/td] [/tr]";

	/*
	487		Petit B.
	494		Grand B.
	501		interception
	508 	interplanetaire
	*/

	string petit[nb_planets];
	string grand[nb_planets];
	string mi[nb_planets];
	string mip[nb_planets];

	per_planet_values(petit, 	str[487]);
	per_planet_values(grand, 	str[494]);
	per_planet_values(mi, 		str[501]);
	per_planet_values(mip, 		str[508]);

	for(int i = 0; i < nb_planets; ++i)
	{
		convert << i + 1;

		index_string = convert.str();

		bbcode = bbcode + "[tr] [td] [center]Planete " + index_string + "\ncoordonnees[/center] [/td][td][center]" + petit[i] + "[/center] [/td][td][center]" + grand[i] + "[/center] [/td][td][center]" + mi[i] + "[/center] [/td][td][center]" + mip[i] + "[/center] [/td] [/tr]";

		convert.str("");
	}

	bbcode = bbcode + "[/table]";
}

void technologie()
{
	string energie 			= str[367];
	string laser 			= str[376];
	string ions 			= str[373];
	string hyperespace 		= str[370];
	string plasma  			= str[379];
	string combustion 		= str[355];
	string impulsion 		= str[359];
	string propulsion 		= str[362];

	string espionnage		= str[345];
	string ordi 			= str[351];
	string astro 			= str[386];
	string reseau 			= str[384];
	string graviton			= str[389];
	string armes 			= str[333];
	string bouclier 		= str[336];
	string protection 		= str[342];

	bbcode = bbcode + "[img]http://s6.postimage.org/638andbht/technologies.png[/img]\n\n[table border=4 align = center][tr][td] [center][img]http://s6.postimage.org/s47itvh4d/energyw.png[/img]\n Energy[/center] [/td][td] [center][img]http://s6.postimage.org/havf7magd/laserm.png[/img]\n Laser[/center] [/td][td] [center][img]http://s6.postimage.org/sly2vzhbh/ions.png[/img]\n Ions[/center] [/td][td] [center][img]http://s6.postimage.org/74mtomq25/hyperespace.png[/img]\n Hyper.[/center] [/td][td] [center][img]http://s6.postimage.org/yb97vn4od/plasmac.png[/img]\n Plasma[/center] [/td][td] [center][img]http://s6.postimage.org/o7ysbmlil/combustion.png[/img]\n Comb.[/center] [/td][td] [center][img]http://s6.postimage.org/tj4i4ustp/impulsion.png[/img]\n Impul.[/center] [/td][td] [center][img]http://s6.postimage.org/u789358q5/propulsion.png[/img]\n Prop.H[/center] [/td] [/tr][tr] [td][center]" + energie + "[/center][/td] [td][center]" + laser + "[/center][/td] [td][center]" + ions + "[/center][/td] [td][center]" + hyperespace + "[/center][/td] [td][center]" + plasma + "[/center][/td] [td][center]" + combustion + "[/center][/td] [td][center]" + impulsion + "[/center][/td] [td][center]" + propulsion + "[/center][/td] [/tr][tr] [td] [center][img]http://s6.postimage.org/i86fu8bcd/espionnagec.png[/img]\n Espio.[/center] [/td][td] [center][img]http://s6.postimage.org/e1bwgi3jh/ordinateurl.png[/img]\n Ordi.[/center] [/td][td] [center][img]http://s6.postimage.org/3k04ww0a5/astrophysique.png[/img]\n Astro.[/center] [/td][td] [center][img]http://s6.postimage.org/47up3p1f1/reseau.png[/img]\n Reseau.[/center] [/td][td] [center][img]http://s6.postimage.org/qvo8lzejx/graviton.png[/img]\n Gravi.[/center] [/td][td] [center][img]http://s6.postimage.org/be0qia831/armeye.png[/img]\n Armes[/center] [/td][td] [center][img]http://s6.postimage.org/jsbrsmjql/bouclierb.png[/img]\n Boucl.[/center] [/td][td] [center][img]http://s6.postimage.org/5o1m83ey5/protectionx.png[/img]\n Protec.[/center] [/td] [/tr][tr] [td][center]" + espionnage + "[/center][/td] [td][center]" + ordi + "[/center][/td] [td][center]" + astro + "[/center][/td] [td][center]" + reseau + "[/center][/td] [td][center]" + graviton + "[/center][/td] [td][center]" + armes + "[/center][/td] [td][center]" + bouclier + "[/center][/td] [td][center]" + protection + "[/center][/td] [/tr] [/table]";
}

void flottes()
{
	string cles 			= str[416];
	string clos 			= str[419];
	string croiseurs		= str[421];
	string vbs		 		= str[425];
	string pts	 			= str[395];
	string gts		 		= str[398];
	string colo 			= str[402];

	string traqueurs		= str[427];
	string bbs 	 			= str[429];
	string dds 	 			= str[431];
	string rips 			= str[436];
	string recycleurs		= str[404];
	string sondes 			= str[407];

	bbcode = bbcode + "[img]http://s6.postimage.org/nbetsjzht/flotte.png[/img]\n\n[table border=4 align = center][tr][td] [center][img]http://s6.postimage.org/4ibwlfo8d/cles.png[/img]\n Cles[/center] [/td][td] [center][img]http://s6.postimage.org/gvoqscdwt/closa.png[/img]\n Clos[/center] [/td][td] [center][img]http://s6.postimage.org/3p3w6k7l9/crs.png[/img]\n Crs.[/center] [/td][td] [center][img]http://s6.postimage.org/3xil6lxf1/vbs.png[/img]\n VB.[/center] [/td][td] [center][img]http://s6.postimage.org/smybr0ay5/87846336.png[/img]\n Pt.[/center] [/td][td] [center][img]http://s6.postimage.org/lize7uqnh/22297852.png[/img]\n GT.[/center] [/td][td] [center][img]http://s6.postimage.org/3zbepwm7h/colov.png[/img]\n Colon.[/center] [/td] [/tr][tr] [td][center]" + cles + "[/center][/td]  [td][center]" + clos + "[/center][/td] [td][center]" + croiseurs + "[/center][/td] [td][center]" + vbs + "[/center][/td] [td][center]" + pts + "[/center][/td] [td][center]" + gts + "[/center][/td] [td][center]" + colo + "[/center][/td] [/tr][tr] [td] [center][img]http://s6.postimage.org/s2jaobhpp/trsc.png[/img]\n Trs.[/center] [/td][td] [center][img]http://s6.postimage.org/9waoszdyl/69728890.png[/img]\n BB.[/center] [/td][td] [center][img]http://s6.postimage.org/h7asiujql/41720557.png[/img]\n DD.[/center] [/td][td] [center][img]http://s6.postimage.org/ftj5njkh9/edlm.png[/img]\n EDLM[/center] [/td][td] [center][img]http://s6.postimage.org/bhbo8nqlp/recyclos.png[/img]\n Rc.[/center] [/td][td] [center][img]http://s6.postimage.org/rje7f1qb1/sondes.png[/img]\n Sondes[/center] [/td] [/tr][tr] [td][center]" + traqueurs + "[/center][/td] [td][center]" + bbs + "[/center][/td] [td][center]" + dds + "[/center][/td] [td][center]" + rips + "[/center][/td] [td][center]" + recycleurs + "[/center][/td] [td][center]" + sondes + "[/center][/td] [/tr] [/table][/color][/center]";
}

void final_bbcode()
{
	ofstream out("empire_out.txt");
	if (out.is_open())
	{
		out << bbcode;
		out.close();
	}

	else
	{
		cout << "Unable to open file" << endl;
		exit(EXIT_FAILURE);
	}


}

int main(int argc, char const *argv[])
{
	//testparser("empire_in.txt");
	openfile("empire_in.txt");
	check_nb_planets();
	title();
	classement();
	points();
	production();
	ressources();
	installations();
	defenses();
	technologie();
	flottes();
	final_bbcode();

	return EXIT_SUCCESS;
}

