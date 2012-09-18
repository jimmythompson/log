#include "Log.h"
#include <ctime>
#include <iostream>

/**
 * @brief Constructor
 */
Log::Log()
	: m_threshold( INFO ),
	  m_fileName(),
	  m_stack(),
	  m_stream() {
}

/**
 * @brief Copy constructor
 * @details Kept private in order to preserve singleton
 */
Log::Log(const Log&) {
}

/**
 * @brief Copy operator
 * @details Kept private in order to preserve singleton
 */
Log& Log::operator=(const Log&) {
	return *this;
}

/**
 * @brief Destructor
 * @details Logs the shut down then closes the file stream
 */
Log::~Log() {
	if( m_initialised ) {
		info( "Log shutting down" );
		m_stream.close();
	}
}

/**
 * @brief Get the singleton instance
 */
Log& Log::get() {
	static Log log;
	return log;
}

/**
 * @brief Gets the name of the log category from the enum value
 *
 * @param The enum value of the category
 * @return The name of the category; returns the word UNKNOWN if not valid.
 */
const char* Log::typeToString(Type type) {
	switch(type) {
	case FATAL:
		return "FATAL";
	case ERROR:
		return "ERROR";
	case WARN:
		return "WARN";
	case INFO:
		return "INFO";
	case DEBUG:
		return "DEBUG";
	default:
		break;
	}
	return "UNKNOWN";
}

/**
 * @brief Initialises the file stream
 *
 * @param fileName The location of the file to create/append to
 * @return True if the file was successfully initialised; false if already initialised
 */
bool Log::initialise( const std::string& fileName ) {
	Log& log = Log::get();

	if( !log.m_initialised ) {
		log.m_fileName = fileName;
		log.m_stream.open( fileName.c_str(), std::ios_base::app | std::ios_base::out );
		log.m_initialised = true;
		info( "Log initialised" );
		return true;
	}
	return false;
}

/**
 * @brief Initialises the file stream
 *
 * @param fileName The location of the file to create/append to
 * @return True if the file was successfully initialised; false if already initialised
 */
bool Log::initialise( const char* fileName ) {
	return initialise( std::string( fileName ) );
}

/**
 * @brief Writes the specified message to the console and the log file
 *
 * @param message The message to write
 */
void Log::write( const std::string& message ) {
	std::cout << message << std::endl;
	m_stream  << message << std::endl;
}

/**
 * @brief Writes the specified message to the console and the log file
 *
 * @param message The message to write
 */
void Log::write( const char* message ) {
	write( std::string( message ) );
}

/**
 * @brief Logs the specified message with a timestamp and category prefix
 *
 * @param type The category of message to write based on the enum Log::Type
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::log( const Type type, const std::string& message ) {
	if( type <= m_threshold ) {
		std::string prefix( "[ TIME ] " );
		//prefix.append(m_stack.size(), ' ');

		write( prefix + std::string( typeToString(type) ) + "	" + message );

		/* If it's an error (or worse), dump the stack.
		if( type <= ERROR ) {
			write( "====== Stack Trace ======" );
			for( std::vector<std::string>::reverse_iterator i = m_stack.rbegin(); i != m_stack.rend(); ++i) {
				write( *i );
			}
			write( "=========================" );
		}
		*/
		return true;
	}
	return false;
}

/**
 * @brief Writes a fatal error to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::fatal( const std::string& message ) {
	return Log::get().log( FATAL, message );
}

/**
 * @brief Writes a fatal error to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::fatal( const char* message ) {
	return fatal( std::string( message ) );
}

/**
 * @brief Writes an error to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::error( const std::string& message ) {
	return Log::get().log( ERROR, message );
}

/**
 * @brief Writes an error to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::error( const char* message ) {
	return error( std::string( message ) );
}

/**
 * @brief Writes a warning to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::warn( const std::string& message ) {
	return Log::get().log( WARN, message );
}

/**
 * @brief Writes a warning to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::warn( const char* message ) {
	return warn( std::string( message ) );
}

/**
 * @brief Writes an information message to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::info( const std::string& message ) {
	return Log::get().log( INFO, message );
}

/**
 * @brief Writes an information message to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::info( const char* message ) {
	return info( std::string( message ) );
}

/**
 * @brief Writes a debug message to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::debug( const std::string& message ) {
	return Log::get().log( DEBUG, message );
}

/**
 * @brief Writes a debug message to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::debug( const char* message ) {
	return debug( std::string( message ) );
}

/**
 * @brief Peeks at the top element of the function stack
 *
 * @return The top element of the function stack
 */
std::string Log::peek() {
	return Log::get().m_stack.back();
};

/**
 * @brief Pushes the function stack with the given message
 *
 * @param input The message to store in the stack (typically the name of the function)
 * @return True if the stack was successfully pushed
 */
bool Log::push( const std::string& input ) {
	if( !input.empty() ) {
		info( input + " - BEGIN" );
		Log::get().m_stack.push_back( input );
		return true;
	}
	return false;
}

/**
 * @brief Pushes the function stack with the given message
 *
 * @param input The message to store in the stack (typically the name of the function)
 * @return True if the stack was successfully pushed
 */
bool Log::push( const char* input ) {
	return push( std::string( input ) );
}

/**
 * @brief Pops the top element off the stack
 *
 * @return The message just popped off the stack
 */
std::string Log::pop() {
	Log& log = Log::get();
	if( !log.m_stack.empty() ) {
		std::string temp( log.peek() );
		log.m_stack.pop_back();
		info( temp + " - END" );
		return temp;
	}
	return std::string();
}
