#include "Log.h"
#include <ctime>
#include <iostream>

Log::Log()
	: m_threshold( INFO ),
	  m_fileName(),
	  m_stack(),
	  m_stream() {
}

Log::Log(const Log&) {
}

Log::~Log() {
	if( m_initialised ) {
		m_stream.close();
	}
}

Log& Log::instance() {
	static Log log;
	return log;
}

bool Log::initialise( const std::string& fileName ) {
	if( !m_initialised ) {
		m_fileName = fileName;
		m_stream.open( fileName.c_str(), std::ios_base::app | std::ios_base::out );
		m_initialised = true;
		return true;
	}
	return false;
}

bool Log::initialise( const char* fileName ) {
	return initialise( std::string( fileName ) );
}

void Log::write( const std::string& message ) {
	std::cout << message << std::endl;
	m_stream  << message << std::endl;
}

void Log::write( const char* message ) {
	write( std::string( message ) );
}

bool Log::log( const Type type, const std::string& message ) {
	if( type <= m_threshold ) {
		std::string prefix( "[ TIME ] " );
		prefix.append(m_stack.size(), ' ');

		write( prefix + message );

		//If it's an error, dump the stack.
		if( type <= ERROR ) {
			write( "====== Stack Trace ======" );
			for( std::vector<std::string>::reverse_iterator i = m_stack.rbegin(); i != m_stack.rend(); ++i) {
				write( *i );
			}
			write( "=========================" );
		}
		return true;
	}
	return false;
}

bool Log::error( const std::string& message ) {
	return log( ERROR, message );
}

bool Log::error( const char* message ) {
	return error( std::string( message ) );
}

bool Log::info( const std::string& message ) {
	return log( INFO, message );
}

bool Log::info( const char* message ) {
	return info( std::string( message ) );
}

bool Log::debug( const std::string& message ) {
	return log( DEBUG, message );
}

bool Log::debug( const char* message ) {
	return debug( std::string( message ) );
}

std::string Log::peek() {
	return m_stack.back();
};

bool Log::push( const std::string& input ) {
	if( !input.empty() ) {
		info( "[BEGIN] " + input );
		m_stack.push_back( input );
		return true;
	}
	return false;
}

bool Log::push( const char* input ) {
	return push( std::string( input ) );
}

bool Log::pop() {
	if( !m_stack.empty() ) {
		std::string temp( peek() );
		m_stack.pop_back();
		info( "[END] " + temp );
		return true;
	}
	return false;
}
