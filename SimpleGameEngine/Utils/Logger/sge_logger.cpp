//
// Created by Janusz Majchrzak on 30/05/17.
//

#include "sge_logger.hpp"
#ifdef _WIN32
	#include <boost/config/platform/win32.hpp>
	//posix_time needs BOOST_HAS_FTIME which is defined here.
#endif
#include <boost/date_time/posix_time/posix_time.hpp>

std::mutex SGE::LoggerFactory::logger_sync;

SGE::Logger::Logger(std::mutex &mutex_ref, const std::string _component_name) :
        mu{mutex_ref}, component_name{_component_name}
{
}

std::shared_ptr<SGE::Logger> SGE::Logger::instance(const std::string component_name)
{
    return SGE::LoggerFactory::create_logger(component_name);
}

std::string SGE::Logger::getTimestamp()
{
    boost::posix_time::ptime posix_time = boost::posix_time::microsec_clock::local_time();
    return boost::posix_time::to_simple_string(posix_time);
}

std::shared_ptr<SGE::Logger> SGE::LoggerFactory::create_logger(const std::string component_name)
{
    return std::shared_ptr<SGE::Logger>(new SGE::Logger(SGE::LoggerFactory::logger_sync, component_name));
}

std::shared_ptr<SGE::LoggerError> SGE::LoggerFactory::create_logger_error(const std::string component_name)
{
    return std::shared_ptr<SGE::LoggerError>(new SGE::LoggerError(SGE::LoggerFactory::logger_sync, component_name));
}

SGE::LoggerError::LoggerError(std::mutex &mutex_ref, const std::string _component_name) : SGE::Logger(mutex_ref,
                                                                                            _component_name)
{
}

std::shared_ptr<SGE::LoggerError> SGE::LoggerError::instance(const std::string component_name)
{
    return SGE::LoggerFactory::create_logger_error(component_name);
}