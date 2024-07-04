/*
Author 1: Anas Mohamed Refaei --> ID: 20230072
         Has done Filters: 1, 7  
Author 2: Marawan Mohamed Abd El-hamid --> ID: 20230557
		 Has done Filters: 2
Author 3: Zeyad Mustafa Ramadan Amin --> ID: 20230162
		 Has done Filters: 3, 6
*/

#include "Image_Class.h"
#include <string>   

using namespace std;
char ch, c; 


int MENU() {
	
    int choice ;
	cout << "How would you like to flip the picture, sir? \n";
	cout << "1) Horizontal flip.\n";
	cout << "2) Vertical flip.\n";
	cout << "Please select a choice(1/2): ";
	cin >> choice; 
	while (choice != 1 && choice != 2) { 
		cout << endl;
		cout << "ERROR:** Invalid input **\nPlease try again\n";
		MENU();
	}
	return choice; 
}

char choice() 
{
	cout << "A) Darken\nB) Lighten\nC) Grayscale\nD) Black and white\nE) Invert\nF) Rotate\n";
	cout << "G) Merge\nH) Flip\nI) Detect edges\nJ) Resize\nK) Blur\nl) Frame filter\nM) Infrared\nN) Purple filter\n";
	cout << "O) Skew filter\n";
	cin >> ch;

	 c = toupper(ch);
	
	 return c;
		
}

void skew(Image picture, string save)
{
	string degree; 
	cout << "Please enter a degree: ";
	cin.ignore();
	getline(cin, degree);
	double PI = 3.14159265;

	int new_width = picture.width + (picture.height / tan((stoi(degree) * PI) / 180.0));

	Image pic(new_width, picture.height);
	Image img(new_width, picture.height);

	for (int R = 0; R < pic.height; R++) {
		for (int G = 0; G < new_width; G++) {
			if (G <= (pic.height - R) * (picture.height / tan((stoi(degree) * PI) / 180.0) / pic.height)) {
				pic(G, R, 0) = 255;
				pic(G, R, 1) = 255;
				pic(G, R, 2) = 255;
				img(G, R, 0) = 255;
				img(G, R, 1) = 255;
				img(G, R, 2) = 255;
			}
		}
	}

	for (int R = 0; R < img.width / 2; R++) {
		for (int G = 0; G < img.height; G++) {
			for (int B = 0; B < 3; B++) {
				swap(img(R, G, B), img(img.width - R - 1, G, B));
			}
		}
	}
	for (int R = 0; R < img.width; R++) {
		for (int G = 0; G < img.height / 2; G++) {
			for (int B = 0; B < 3; B++) {
				swap(img(R, G, B), img(R, img.height - G - 1, B));
			}
		}
	}

	for (int R = 0; R < pic.width; R++) {
		for (int G = 0; G < pic.height; G++) {
			if (pic(R, G, 0) == 255 || img(R, G, 0) == 255) {
				img(R, G, 0) = 255;
				img(R, G, 1) = 255;
				img(R, G, 2) = 255;
			}
		}
	}
	int red = 0, green = 0;
	for (int G = 0; G < pic.height; G++) {
		red = 0;
		for (int R = 0; R < pic.width; R++) {
			if (img(R, G, 0) == 0) {
				img(R, G, 0) = picture(red, green, 0);
				img(R, G, 1) = picture(red, green, 1);
				img(R, G, 2) = picture(red, green, 2);
				red++;
			}
		}
		green++;

	}
	while (true)
	{
		try {
			img.saveImage(save); 
			system(save.c_str()); 
			break;
		}
		catch (...)
		{
			cout << "Please enter a valid format , re-enter the name and format" << endl; 
			cin.ignore(); 
			getline(cin, save); 
		}
	}
}

void fancyW(Image& image, int j)
{
	double dstnc = 0.02;

	double flag = image.width - (dstnc * 2 * image.width);

	for (int l = image.width * dstnc; l <= dstnc * 2 * image.width; l += 3)
	{
		image(l, j, 0) = 255;
		image(l, j, 1) = 255;
		image(l, j, 2) = 255;
	}
	for (int l = flag ; l <= (image.width - image.width * dstnc); l += 3)
	{
		image(l, j, 0) = 255;
		image(l, j, 1) = 255;
		image(l, j, 2) = 255;
	}
}

void fancyH(Image& image, int i)
{
	double dstnc = 0.019;
	double flagh = image.height - (dstnc * 2 * image.width);

	for (int k = image.height * dstnc; k <= dstnc * 2 * image.height; k += 3)
	{
		image(i, k, 0) = 255;
		image(i, k, 1) = 255;
		image(i, k, 2) = 255;
	}
	for (int k = flagh ; k <= (image.height - image.height * dstnc) ; k += 3)
	{
		image(i, k, 0) = 255;
		image(i, k, 1) = 255;
		image(i, k, 2) = 255;
	}
}

void frame(Image picture , string save)
{
	int choice;
	char chose;

	cout << "** Colors option**\n";
	cout << "1) RED.\n";
	cout << "2) BLUE.\n";
	cout << "3) BLACK.\n";
	cout << "4) GREEN.\n";
	cout << "5) GRAY.\n";
	cout << "6) YELLOW.\n";
	cout << "Please select a color (1/6): ";
	
	cin >> choice; 
	while (choice < 1 || choice > 6) {
		cout << '\n';
		cout << "** Invalid input **\n";
		cout << endl;
		cout << "Please select a number between(1/6): ";
		cin.clear();
		cin.ignore();
		cin >> choice;
	}

	cout << "Do you want it regular or fancy: \n";
	cout << "A) Regular    B) Fancy\n";
	cin.clear();
	cin.ignore();
	cin >> chose;
	char choose = toupper(chose);
	while (choose != 'A' && choose != 'B')
	{
		cout << "Not Valid Choice ... insert a valid choic\n";
		cin >> chose;
		choose = toupper(chose);
	}
	
	if (choice == 1) {
		for (int R = 0; R < picture.width; R++) {
			for (int G = 0; G < picture.height; G++) {
				if (R <= picture.width * 0.015 || R >= (picture.width - picture.width * 0.015)) {

					picture(R, G, 0) = 255;
					picture(R, G, 1) = 0;
					picture(R, G, 2) = 0;

					if (choose == 'B')
					{
						fancyW(picture, G);
					}
				}
				if (G <= picture.height * 0.015 || G >= (picture.height - picture.height * 0.015)) {
					picture(R, G, 0) = 255;
					picture(R, G, 1) = 0;
					picture(R, G, 2) = 0;

					if (choose == 'B')
					{
						fancyH(picture, R);
					}
				}
			}
		}
		
	}
	else if (choice == 2) {
		for (int R = 0; R < picture.width; R++) {
			for (int G = 0; G < picture.height; G++) {
				if (R <= picture.width * 0.015 || R >= (picture.width - picture.width * 0.015)) {

					picture(R, G, 0) = 0;
					picture(R, G, 1) = 0;
					picture(R, G, 2) = 255;

					if (choose == 'B')
					{
						fancyW(picture, G);
					}
				}
				if (G <= picture.height * 0.015 || G >= (picture.height - picture.height * 0.015)) {
					picture(R, G, 0) = 0;
					picture(R, G, 1) = 0;
					picture(R, G, 2) = 255;

					if (choose == 'B')
					{
						fancyH(picture, R);
					}
				}
			}
		}
		
	}
	
	else if (choice == 3) {
		for (int R = 0; R < picture.width; R++) {
			for (int G = 0; G < picture.height; G++) {
				if (R <= picture.width * 0.015 || R >= (picture.width - picture.width * 0.015)) {
					for (int B = 0; B < 3; B++) {
						picture(R, G, B) = 0;
					}
					if (choose == 'B')
					{
						fancyW(picture, G); 
					}
				}
				if (G <= picture.height * 0.015 || G >= (picture.height - picture.height * 0.015)) {
					for (int B = 0; B < 3; B++) {
						picture(R, G, B) = 0;
					}
					if (choose == 'B')
					{
						fancyH(picture, R);
					}
				
				}
			}
		}
		
	}

	else if (choice == 4) {
		for (int R = 0; R < picture.width; R++) {
			for (int G = 0; G < picture.height; G++) {
				if (R <= picture.width * 0.015 || R >= (picture.width - picture.width * 0.015)) {

					picture(R, G, 0) = 0;
					picture(R, G, 1) = 255;
					picture(R, G, 2) = 0;


					if (choose == 'B')
					{
						fancyW(picture, G);
					}
				}
				if (G <= picture.height * 0.015 || G >= (picture.height - picture.height * 0.015)) {
					picture(R, G, 0) = 0;
					picture(R, G, 1) = 255;
					picture(R, G, 2) = 0;


					if (choose == 'B')
					{
						fancyH(picture, R);
					}
				}
			}
		}
		
	}

	else if (choice == 5) {
		for (int R = 0; R < picture.width; R++) {
			for (int G = 0; G < picture.height; G++) {
				if (R <= picture.width * 0.015 || R >= (picture.width - picture.width * 0.015)) {

					picture(R, G, 0) = 128;
					picture(R, G, 1) = 128;
					picture(R, G, 2) = 128;

					if (choose == 'B')
					{
						fancyW(picture, G);
					}
				}
				if (G <= picture.height * 0.015 || G >= (picture.height - picture.height * 0.015)) {
					picture(R, G, 0) = 128;
					picture(R, G, 1) = 128;
					picture(R, G, 2) = 128;

					if (choose == 'B')
					{
						fancyH(picture, R);
					}
				}
			}
		}
	}
	else if (choice == 6) {
		for (int R = 0; R < picture.width; R++) {
			for (int G = 0; G < picture.height; G++) {
				if (R <= picture.width * 0.015 || R >= (picture.width - picture.width * 0.015)) {

					picture(R, G, 0) = 255;
					picture(R, G, 1) = 255;
					picture(R, G, 2) = 0;
					if (choose == 'B')
					{
						fancyW(picture, G);
					}
				}
				if (G <= picture.height * 0.015 || G >= (picture.height - picture.height * 0.015)) {
					picture(R, G, 0) = 255;
					picture(R, G, 1) = 255;
					picture(R, G, 2) = 0;


					if (choose == 'B')
					{
						fancyH(picture, R); 
					}
				}
			}
		}
	}
	while (true)
	{
		try {
			picture.saveImage(save);
			system(save.c_str());
			break;
		}
		catch (...)
		{
			cout << "Please enter a valid format , re-enter the name and format" << endl;
			cin.ignore();
			getline(cin, save);
		}
	}
}

void purple(Image picture, string save)
{
	for (int R = 0; R < picture.width; R++) {
		for (int G = 0; G < picture.height; G++) {
			for (int B = 0; B < 3; B++) {

				picture(R, G, 1) = picture(R, G, 1) * 0.87;
			}
		}
	}

	while (true)
	{
		try {
			picture.saveImage(save);
			system(save.c_str());
			break;
		}
		catch (...)
		{
			cout << "Please enter a valid format , re-enter the name and format" << endl;
			cin.ignore();
			getline(cin, save);
		}
	}

}

void inred(Image picture, string save)
{
	for (int R = 0; R < picture.width; R++) {
		for (int G = 0; G < picture.height; G++) {

			picture(R, G, 0) = 245;
			picture(R, G, 1) = 255 - picture(R, G, 1);
			picture(R, G, 2) = 255 - picture(R, G, 2);

		}
	}
	while (true)
	{
		try {
			picture.saveImage(save);
			system(save.c_str());
			break;
		}
		catch (...)
		{
			cout << "Please enter a valid format , re-enter the name and format" << endl;
			cin.ignore();
			getline(cin, save);
		}
	}
}
void blur(Image  image, string save) 
{
	int kernelSize = 19;

	for (int i = 0; i < image.width; i++)
	{
		for (int j = 0; j < image.height; j++)
		{
			int kernel1 = 0;
			int kernel2 = 0;
			int kernel3 = 0;

			for (int k = max(i - kernelSize, i); k < min(kernelSize + i, image.width); k++)
			{
				for (int l = max(j - kernelSize, j); l < min(kernelSize + j, image.height); l++)
				{
					kernel1 += image(k, l, 0);
					kernel2 += image(k, l, 1);
					kernel3 += image(k, l, 2);
				}
			}

			kernel1 /= (kernelSize * kernelSize);
			kernel2 /= (kernelSize * kernelSize);
			kernel3 /= (kernelSize * kernelSize);

			image(i, j, 0) = kernel1;
			image(i, j, 1) = kernel2;
			image(i, j, 2) = kernel3;

		}
	}
	while (true)
	{
		try {
			image.saveImage(save);
			system(save.c_str());
			break;
		}
		catch (...)
		{
			cout << "Please enter a valid format , re-enter the name and format" << endl;
			cin.ignore();
			getline(cin, save);
		}
	}
}
void resize(Image image, string save)
{
	double wid, high, ratiow, ratioh;
	int oldx, oldy;

	cout << "insert the new width and new height of your new image\n";
	cin >> wid >> high;

	Image pic(wid, high);

	ratiow = image.width / wid;
	ratioh = image.height / high;


	for (int i = 0; i < wid; i++)
	{
		oldx = round(i * ratiow);
		for (int j = 0; j < high; j++)
		{
			oldy = round(j * ratioh);

			pic(i, j, 0) = image(oldx, oldy, 0);
			pic(i, j, 1) = image(oldx, oldy, 1);
			pic(i, j, 2) = image(oldx, oldy, 2);

		}
	}
	while (true)
	{
		try {
			pic.saveImage(save);
			system(save.c_str());
			break;
		}
		catch (...)
		{
			cout << "Please enter a valid format , re-enter the name and format" << endl;
			cin.ignore();
			getline(cin, save);
		}
	}
}

int rotate(Image picture, string save)
{
	int choice;
	
	while (true)
	{
		cout << "How would you like to Rotate the picture, sir? \n";
		cout << "1) 90 degree.\n";
		cout << "2) 180 degree.\n";
		cout << "3) 270 degree.\n";
		cout << "Please select a choice(1/2/3): ";
		cin >> choice;
		
		if (choice !=  1 && choice != 2 && choice != 3)
		{
			cout << "ERROR:** Invalid input **\nPlease try again\n";
			cin.clear();
			cin.ignore();
			continue;
		}
		else {
			break;
		}
	}

	if (choice == 1) {
		Image img(picture.height, picture.width);
		for (int R = 0; R < img.width; R++) {
			for (int G = 0; G < img.height; G++) {
				for (int B = 0; B < 3; B++) {
					img(R, G, B) = picture(G, picture.height - R - 1, B);
				}
			}
		}
		while (true)
		{
			try {
				img.saveImage(save); 
				system(save.c_str());
				break;
			}
			catch (...)
			{
				cout << "Please enter a valid format , re-enter the name and format" << endl;
				cin.ignore(); 
				getline(cin, save);
			}
		}
		
		
	}

	else if (choice == 2) {

		for (int R = 0; R < picture.width / 2; R++) {
			for (int G = 0; G < picture.height; G++) {
				for (int B = 0; B < 3; B++) {
					swap(picture(R, G, B), picture(picture.width - R - 1, G, B));
				}
			}
		}
		for (int R = 0; R < picture.width; R++) {
			for (int G = 0; G < picture.height / 2; G++) {
				for (int B = 0; B < 3; B++) {
					swap(picture(R, G, B), picture(R, picture.height - G - 1, B));
				}
			}
		}
		while (true)
		{
			try {
				picture.saveImage(save); 
				system(save.c_str());
				break;
			}
			catch (...)
			{
				cout << "Please enter a valid format , re-enter the name and format" << endl;
				cin.ignore();
				getline(cin, save);
				
			}
		}
		
	}

	else if (choice == 3) {
		Image img(picture.height, picture.width);

		for (int R = 0; R < img.width; R++) {
			for (int G = 0; G < img.height; G++) {
				for (int B = 0; B < 3; B++) {
					img(R, G, B) = picture(picture.width - G - 1, R, B);
				}
			}
		}

		while (true)
		{
			try {
				img.saveImage(save);  
				system(save.c_str());
				break;
			}
			catch (...)
			{
				cout << "Please enter a valid format , re-enter the name and format" << endl;
				cin.ignore();
				getline(cin, save);
			}
		}
	}
	return 0;
}

int invert(Image pic, string save)
{
	
	for (int R = 0; R < pic.width; R++) {
		for (int G = 0; G < pic.height; G++) {
			for (int B = 0; B < 3; B++) {
				pic(R, G, B) = 255 - pic(R, G, B);
			}
		}
	}

	while (true)
	{
		try {
			pic.saveImage(save);
			system(save.c_str());
			break;
		}
		catch (...)
		{
			cout << "Please enter a valid format , re-enter the name and format" << endl;
			cin.ignore();
			getline(cin, save);
		}
	} 
	return 0;
}
int blackAndWhite(Image pic , string save)
{
	for (int R = 0; R < pic.width; R++) {
		for (int G = 0; G < pic.height; G++) {
			unsigned int avg = 0;
			for (int B = 0; B < pic.channels; B++) {

				avg += pic(R, G, B);
			}
			avg = avg / 3;
			for (int B = 0; B < 3; B++) {
				if (avg > 127) {
					pic(R, G, B) = 255;
				}
				else if (avg <= 127) {
					pic(R, G, B) = 0;
				}

			}
		}

	} 
	while (true)
	{
		try {
			pic.saveImage(save); 
			system(save.c_str());
			break;
		}
		catch (...)
		{
			cout << "Please enter a valid format , re-enter the name and format" << endl;
			cin.ignore();
			getline(cin, save);
		}
	}
	return 0;
}

int gray(Image pic, string save)
{
	for (int R = 0; R < pic.width; R++) {
		for (int G = 0; G < pic.height; G++) {
			unsigned int avg = 0;
			for (int B = 0; B < pic.channels; B++) {

				avg += pic(R, G, B);

			}
			avg = avg / 3;
			for (int B = 0; B < 3; B++) {

				pic(R, G, B) = avg;

			}
		}

	}
	while (true)
	{
		try {
			pic.saveImage(save); 
			system(save.c_str());
			break;
		}
		catch (...)
		{
			cout << "Please enter a valid format , re-enter the name and format" << endl;
			cin.ignore();
			getline(cin, save);
		}
	}
	return 0;
}

int imgD(Image image , string save)
{
	for (int i = 0; i < image.width; i++)
	{
		for (int j = 0; j < image.height; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				unsigned int s = 0;
				unsigned int e = 0;
				s = image(i, j, k);
				e = s / 2;
				image(i, j, k) = s - e;
			}
		}
	}

	
	while (true)
	{
		try {
			image.saveImage(save);
			system(save.c_str());
			break;
		}
		catch (...)
		{
			cout << "Please enter a valid format , re-enter the name and format" << endl;
			cin.ignore(); 
			getline(cin, save); 
		}
	} 
	
	return 0;
}

int imgL(Image image , string save) 
{
	for (int i = 0; i < image.width; i++)
	{
		for (int j = 0; j < image.height; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				int s = 0;
				int e = 0;
				s = image(i, j, k);
				e = s * 2;
				image(i, j, k) = min(s + e, 255);
			}
		}
	}
	while (true)
	{
		try {
			image.saveImage(save);
			system(save.c_str());
			break;

		}
		catch (...)
		{
			cout << "Please enter a valid format , re-enter the name and format" << endl;
			cin.ignore();
			getline(cin, save);
		}
	}
	return 0;
}

void merge(Image picture1 , string save)
{
	string name2;
	cout << "enter the name of the second image and its extension: ";
	cin.ignore();
	getline(cin, name2);
	Image picture2;
	while (true)
	{
		try
		{
			picture2.loadNewImage(name2);
			break;

		}
		catch (...)
		{
			cout << "Please enter a valid photo" << endl;
			getline(cin, name2);
		}
	}
	double max_width = max(picture1.width, picture2.width);
	double max_height = max(picture1.height, picture2.height);
	double min_width = min(picture1.width, picture2.width);
	double min_height = min(picture1.height, picture2.height);
	double ratiow, ratioh;
	int oldx, oldy;
	Image img(max_width, max_height);

	ratiow = min_width / max_width;
	ratioh = min_height / max_height;

	for (int R = 0; R < max_width; R++)
	{
		oldx = round(R * ratiow);
		for (int G = 0; G < max_height; G++)
		{
			oldy = round(G * ratioh);
			if (picture1.height > picture2.height) {
				for (int B = 0; B < 3; B++) {
					img(R, G, B) = picture2(oldx, oldy, B);
				}

			}
			else {
				for (int B = 0; B < 3; B++) {
					img(R, G, B) = picture1(oldx, oldy, B);
				}
			}
		}
	}

	Image image(max_width, max_height);
	for (int R = 0; R < max_width; R++) {
		for (int G = 0; G < max_height; G++) {
			for (int B = 0; B < 3; B++) {
				if (img.height == picture1.height) {
					image(R, G, B) = img(R, G, B) * 0.5 + picture1(R, G, B) * 0.5;
				}
				else {
					image(R, G, B) = img(R, G, B) * 0.5 + picture2(R, G, B) * 0.5;
				}

			}
		}
	}

	while (true)
	{
		try {
			image.saveImage(save);
			system(save.c_str());
			break;

		}
		catch (...)
		{
			cout << "Please enter a valid format , re-enter the name and format" << endl;
			cin.ignore();
			getline(cin, save);
		}
	}
	
}
void flip(Image picture, string save)
{
	int choice = MENU();
	if (choice == 1) {
		for (int R = 0; R < picture.width / 2; R++) {
			for (int G = 0; G < picture.height; G++) {
				for (int B = 0; B < 3; B++) {
					swap(picture(R, G, B), picture(picture.width - R - 1, G, B));
				}
			}
		}
	}
	else if (choice == 2) {
		for (int R = 0; R < picture.width; R++) {
			for (int G = 0; G < picture.height / 2; G++) {
				for (int B = 0; B < 3; B++) {
					swap(picture(R, G, B), picture(R, picture.height - G - 1, B));
				}
			}
		}
	}
	while (true)
	{
		try {
			picture.saveImage(save);
			system(save.c_str());
			break;

		}
		catch (...)
		{
			cout << "Please enter a valid format , re-enter the name and format" << endl;
			cin.ignore();
			getline(cin, save);
		}
	}
 }

void edge(Image pic, string save)
{
	Image save1(pic.width, pic.height);

	for (int R = 0; R < pic.width; R++) {
		for (int G = 0; G < pic.height; G++) {
			double avg = 0;
			avg += pic(R, G, 0);
			avg += pic(R, G, 1);
			avg += pic(R, G, 2);
			avg /= 3;
			for (int B = 0; B < 3; B++) {
				pic(R, G, B) = avg;
			}
		}
	}

	for (int R = 0; R < pic.width; R++) {
		for (int G = 0; G < pic.height; G++) {
			for (int B = 0; B < 3; B++) {
				save1(R, G, B) = 255;
			}
		}
	}
	for (int R = 1; R < pic.width - 1; R++) {
		for (int G = 1; G < pic.height - 1; G++) {
			if (abs(pic(R, G - 1, 0) - pic(R, G + 1, 0)) > 33 || abs(pic(R - 1, G, 0) - pic(R + 1, G, 0)) > 33) {
				for (int B = 0; B < 3; B++) {
					save1(R, G, B) = 0;
				}
			}


		}

	}
	while (true)
	{
		try {
			save1.saveImage(save);
			system(save.c_str());
			break;

		}
		catch (...)
		{
			cout << "Please enter a valid format , re-enter the name and format" << endl;
			cin.ignore();
			getline(cin, save);
		}
	}
	
}
int main()
{
	
		string name, save;

		cout << "please enter your image name and its extension: ";
		getline(cin, name);
		Image pic; 
		while (true)
		{
			try 
			{
				pic.loadNewImage(name);  
				break;

			}
			catch (...) 
			{
				cout << "Please enter a valid photo" << endl;
				getline(cin, name);
			}
		}

		cout << "please enter the new name of your image and the new extension to be saved: ";
		
		getline(cin, save);
		
		cout << "choose the filter: \n";

		
		while (true) {

			choice(); 

			if (c == 'A')
			{
				imgD(pic, save);
				break;
			}
			else if (c == 'B')
			{
				imgL(pic, save);
				break;
			}
			else if (c == 'C')
			{
				gray(pic, save);
				break;
			}
			else if (c == 'D')
			{
				blackAndWhite(pic, save);
				break;
			}
			else if (c == 'E')
			{
				invert(pic, save);
				break;
			}
			else if (c == 'F')
			{
				rotate(pic, save);
				break;
			}
			else if (c == 'G')
			{
				merge(pic, save);
				break;
			}
			else if (c == 'H')
			{
				flip(pic, save);
				break;
			}
			else if (c == 'I')
			{
				edge(pic, save);
				break;
			}
			else if (c == 'J')
			{
				resize(pic, save);
				break;
			}
			else if (c == 'K')
			{
				blur(pic, save);
				break;
			}
			else if (c == 'L')
			{
				frame(pic, save);
				break;
			}
			else if (c == 'M')
			{
				inred(pic, save);
				break;
			}
			else if (c == 'N')
			{
				purple(pic, save);
				break;
			}
			else if (c == 'O')
			{
				skew(pic, save);
				break;
			}
			else
			{
				cout << "not valid ... please enter a valid choice \n";
				continue;
			}
		}

		cout << "do you want any thing else?? ";
		while (true)
		{
			cout << "A) Yes    B)Exit\n";
			cin >> c;
			c = toupper(c);

			if (c == 'A')
			{
				cin.ignore();
				main();
			}
			else if (c == 'B')
			{
				cout << "thank you";
				break;

			}
			else
			{
				cout << "please enter a valid choice: \n";
				continue;
			}
		}
	
	return 0; 
}