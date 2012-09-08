#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include <vector>

#define PUSH_LOG_STACK Log::instance().push( __FUNCTION__ );
#define POP_LOG_STACK  Log::instance().pop();

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

		bool error( const std::string& message );
		bool error( const char* message );

		bool info( const std::string& message );
		bool info( const char* message );

		bool debug( const std::string& message );
		bool debug( const char* message );

		std::string peek();
		bool push(const std::string& input);
		bool push(const char* input);
		bool pop();
};

#endif
