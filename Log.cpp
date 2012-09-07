#include "Log.h"
#include <ctime>
#include <iostream>

Log::Log()
	: m_threshold( INFO ), m_fileName(), m_stack(), m_stream() {
}

Log::Log(const Log&) {
}

Log::~Log() {
}

Log& Log::instance() {
	static Log log;
	return log;
}

bool Log::initialise( const std::string& fileName ) {
	if(!m_initialised) {
		m_stream.open( fileName.c_str(), std::ios_base::app | std::ios_base::out );
		m_initialised = true;
	}
	return m_initialised;
}

bool Log::initialise( const char* fileName ) {
	return initialise( std::string( fileName ) );
}

bool Log::log( const Type type, const std::string& message ) {
	if(type <= m_threshold) {
		std::string temp( "[ TIME ] " );

		for(size_t i = 0; i < m_stack.size(); ++i ) {
			temp += "- ";
		}

		temp += message;
		std::cout << temp << std::endl;
		m_stream << temp << std::endl;
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
		info( input + " BEGIN" );
		m_stack.push_back( input );
		return true;
	}
	return false;
}

bool Log::push( const char* input ) {
	return push( std::string( input ) );
}

void Log::pop() {
	std::string temp( peek() );
	m_stack.pop_back();
	info( temp + " END" );
}
