#ifndef ColorPalette_Header
#define ColorPalette_Header

class ColorPalette
{
	public:
		ColorPalette();
		~ColorPalette();

		void GenerateColorTables();
		void GenerateRedColorTable();
		void GenerateGreenColorTable();
		void GenerateBlueColorTable();
		void GenerateBlackColorTable();
		void GenerateWhiteColorTable();

	protected:
	private:
};

#endif
