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
	Finalise();
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
const char* Log::TypeToString(Type type) {
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
bool Log::Initialise( const std::string& fileName ) {
	Log& log = Log::get();

	if( !log.m_initialised ) {
		log.m_fileName = fileName;
		log.m_stream.open( fileName.c_str(), std::ios_base::app | std::ios_base::out );
		log.m_initialised = true;
		Info( "LOG INITIALISED" );
		return true;
	}
	return false;
}

/**
 * @brief Finalises the file stream
 *
 * @return True if the file was successfully finalised; false if not initialised
 */
bool Log::Finalise() {
	Log& log = Log::get();

	if( log.m_initialised ) {
		Info( "LOG FINALISED" );
		log.m_stream.close();
		return true;
	}
	return false;
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
 * @brief Logs the specified message with a timestamp and category prefix
 * @details The constant TIMESTAMP_BUFFER_SIZE was calculated as the maximum
 * @details number of characters required for the timestamp
 * @details "[HH:MM:SS MM/DD/YY] "
 *
 * @param type The category of message to write based on the enum Log::Type
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::log( const Type type, const std::string& message ) {
	static const int TIMESTAMP_BUFFER_SIZE = 21;
	
	if( type <= m_threshold ) {
		char buffer[21];
		time_t timestamp;
		time( &timestamp );
		strftime( buffer, sizeof( buffer ), "[%X %x] ", localtime(&timestamp) );

		write( std::string( buffer ) + std::string( TypeToString(type) ) + "	" + message );
		return true;
	}
	return false;
}


/**
 * @brief Sets the debugging threshold
 * @details This is the debugging threshold to use when reporting bugs, useful
 * @details for having lots of debugging information that sometimes you just
 * @details want to turn off.
 *
 * @param type The given debugging threshold to use
 */
void Log::SetThreshold( Type type ) {
	Log& log = Log::get();
	log.m_threshold = type;
}

/**
 * @brief Writes a Fatal Error to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::Fatal( const std::string& message ) {
	return Log::get().log( FATAL, message );
}

/**
 * @brief Writes an Error to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::Error( const std::string& message ) {
	return Log::get().log( ERROR, message );
}

/**
 * @brief Writes a warning to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::Warn( const std::string& message ) {
	return Log::get().log( WARN, message );
}

/**
 * @brief Writes an information message to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::Info( const std::string& message ) {
	return Log::get().log( INFO, message );
}

/**
 * @brief Writes a Debug message to the log
 *
 * @param message The message to log
 * @return True if the log was successful
 */
bool Log::Debug( const std::string& message ) {
	return Log::get().log( DEBUG, message );
}

/**
 * @brief Peeks at the top element of the function stack
 *
 * @return The top element of the function stack
 */
std::string Log::Peek() {
	return Log::get().m_stack.back();
};

/**
 * @brief Pushes the function stack with the given message
 *
 * @param input The message to store in the stack (typically the name of the function)
 * @return True if the stack was successfully pushed
 */
bool Log::Push( const std::string& input ) {
	if( !input.empty() ) {
		Info( input + " - BEGIN" );
		Log::get().m_stack.push_back( input );
		return true;
	}
	return false;
}

/**
 * @brief Pops the top element off the stack
 *
 * @return The message just popped off the stack
 */
std::string Log::Pop() {
	Log& log = Log::get();
	if( !log.m_stack.empty() ) {
		std::string temp( log.Peek() );
		log.m_stack.pop_back();
		Info( temp + " - END" );
		return temp;
	}
	return std::string();
}

/**
 * @brief Writes the stack to the log
 */
void Log::PrintStackTrace() {
	Log& log = Log::get();
	std::string temp;

	for( std::vector<std::string>::reverse_iterator i = log.m_stack.rbegin(); i != log.m_stack.rend(); ++i) {
		temp += *i + "\n";
	}

	log.write( temp );
}