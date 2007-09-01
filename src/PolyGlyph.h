#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
#include <map>

#ifndef __APPLE__
#include "GL/gl.h"
#include "GL/glu.h"
#else
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#endif

#include <ft2build.h>
#include FT_FREETYPE_H

#ifndef FLUXUS_POLY_GLYPH
#define FLUXUS_POLY_GLYPH

using namespace std;


class GlyphGeometry
{
public:
	GlyphGeometry() {}
	~GlyphGeometry() {}
	
	template<class T>
	class Vec3
	{
	public:
		Vec3(T a, T b, T c) : x(a), y(b), z(c) {}
		T x,y,z;
	};
	
	class Mesh
	{
	public:
		Mesh(GLenum type) : m_Type(type) {}
		~Mesh() {}

		GLenum m_Type;
		vector<Vec3<float> > m_Data;
	};

	GLenum m_Error;
	vector<Mesh> m_Meshes;
};

class PolyGlyph
{
public:
	PolyGlyph(const string &ttffile);
	~PolyGlyph();
	
	void Render(wchar_t ch);
	float CharacterWidth(wchar_t ch);
	float CharacterHeight(wchar_t ch);

private:
	
	void Generate(wchar_t ch);
	void BuildGeometry(const FT_GlyphSlot glyph, GlyphGeometry &geo);
	void RenderGeometry(const GlyphGeometry &geo);

	FT_Library    m_Library;
	FT_Face       m_Face;
	FT_GlyphSlot  m_Slot;
	
	map<wchar_t,int> m_Cache;
		
	static void TessError(GLenum errCode, GlyphGeometry* geo);
	static void TessVertex(void* data, GlyphGeometry* geo);
	static void TessCombine(double coords[3], void* vertex_data[4], float weight[4], void** outData, GlyphGeometry* geo);
	static void TessBegin(GLenum type, GlyphGeometry* geo);
	static void TessEnd(GlyphGeometry* geo);

};

#endif