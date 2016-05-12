#ifndef TEXTPOSITION_H
#define TEXTPOSITION_H

class TextPosition
{
	int lineNumber;
	int charNumber;
public:
	TextPosition(int _linenumber = 1, int _charNumber = 1);
	~TextPosition();

	int getLineNumber();
	int getCharNumber();

	void setLineNumber(int newLineNumber);
	void setCharNumber(int newCharNumber);

	void incrementLineNumber();
	void incrementCharNumber();
};

#endif
