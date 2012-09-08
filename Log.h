#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include <vector>

/**
 * @def PUSH_LOG_STACK
 * @brief Pushes the logging stack with the function name that called it
 */
#define PUSH_LOG_STACK Log::instance().push( __FUNCTION__ );

/**
 * @def POP_LOG_STACK
 * @brief Pops the logging stack
 */
#define POP_LOG_STACK  Log::instance().pop();

/**
 * @class Log
 * @brief Basic logging class
 * @author Jimmy Thompson
 *
 * @version $Revision: 1.0 $
 * @date $Date: 2012/09/08 - 14:25:00 $
 * 
 * @details Logging class to deal with basic string messages and
 * @details macro-based stack tracing. Something quick I made to
 * @details handle logging in my own programs; made to be basic.
 */
class Log {
	public:
		static const enum Type {
			FATAL,
			ERROR,
			WARN,
			INFO,
			DEBUG
		};

	private:
		Type m_threshold;
		bool m_initialised;
		std::string m_fileName;
		std::vector<std::string> m_stack;
		std::ofstream m_stream;

		Log();
		Log(const Log&);
		~Log();

		void write( const std::string& message );
		void write( const char* message );

		bool log( const Type type, const std::string& message );

	public:
		static Log& instance();

		bool initialise( const std::string& fileName );
		bool initialise( const char* fileName );

		bool fatal( const std::string& message );
		bool fatal( const char* message );

		bool error( const std::string& message );
		bool error( const char* message );

		bool warn( const std::string& message );
		bool warn( const char* message );

		bool info( const std::string& message );
		bool info( const char* message );
		
		bool debug( const std::string& message );
		bool debug( const char* message );

		//Prefix to string
		std::string peek();
		bool push(const std::string& input);
		bool push(const char* input);
		std::string pop();
};

#endif
