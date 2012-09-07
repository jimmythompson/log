#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include <vector>

#define PUSH_LOG_STACK Log::instance().push( __FUNCTION__ );
#define POP_LOG_STACK Log::instance().pop();

class Log {
	private:
		static const enum Type {
			ERROR,
			INFO,
			DEBUG
		};

		bool m_initialised;
		Type m_threshold;
		std::string m_fileName;
		std::vector<std::string> m_stack;
		std::ofstream m_stream;

		Log();
		Log(const Log&);
		~Log();

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
		void pop();
};

#endif
