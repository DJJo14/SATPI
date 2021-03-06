/* StringConverter.h

   Copyright (C) 2015 Marc Postema (m.a.postema -at- alice.nl)

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
   Or, point your browser to http://www.gnu.org/copyleft/gpl.html
*/
#ifndef STRING_CONVERTER_H_INCLUDE
#define STRING_CONVERTER_H_INCLUDE

#include <string>
#include <linux/dvb/frontend.h>


/// The class @c StringConverter has some string manipulation functions
class StringConverter  {
	public:
		/// Get next line with line_delim (if available) from msg
		/// @return @c true if there is a line found @c false if none was found
		static bool getline(const std::string &msg, std::string::size_type &begin, std::string &line, const char *line_delim);

		///
		static std::string makeXMLString(const std::string &msg);

		///
		static void addFormattedString(std::string &str, const char *fmt, ...);

		///
		static bool isRootFile(const std::string &msg);

		///
		static bool getRequestedFile(const std::string &msg, std::string &file);

		///
		static void splitPath(const std::string &fullPath, std::string &path, std::string &file);

		///
		static bool getMethod(const std::string &msg, std::string &method);

		///
		static bool hasTransportParameters(const std::string &msg);

		///
		static bool getHeaderFieldParameter(const std::string &msg, const std::string &header_field, std::string &parameter);

		///
		static bool getStringParameter(const std::string &msg, const std::string &header_field,
		                               const std::string &parameter, std::string &value);

		///
		static double getDoubleParameter(const std::string &msg, const std::string &header_field, const std::string &parameter);

		///
		static int getIntParameter(const std::string &msg, const std::string &header_field, const std::string &parameter);

		///
		static fe_delivery_system_t getMSYSParameter(const std::string &msg, const std::string &header_field);

		static const char *transmode_to_string(int transmission_mode);
		static const char *rolloff_to_sting(int rolloff);
		static const char *modtype_to_sting(int modtype);
		static const char *fec_to_string(int fec);
		static const char *delsys_to_string(int delsys);
		static const char *guardinter_to_string(int guard_interval);
		static const char *pilot_tone_to_string(int pilot);

}; // class StringConverter

#endif // STRING_CONVERTER_H_INCLUDE