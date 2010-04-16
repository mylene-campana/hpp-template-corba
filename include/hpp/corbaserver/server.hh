// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, JRL.
//
// This file is part of the hpp-corbaserver.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HPP_HRP2SERVER_SERVER_HH
# define HPP_HRP2SERVER_SERVER_HH
# include <hpp/corbaserver/fwd.hh>
# include <hpp/corbaserver/config.hh>

/**

   This Corba server of Library Hpp is mainly implemented by class
   ChppciServer. This class basically:

   \li initializes a Corba server that implements several interfaces
   defined by the following modules,

   \li instantiate an object ChppPlanner a pointer to which is stored
   in ChppciServer::hppPlanner.

   The Corba interfaces trigger actions processed by ChppPlanner
   object. More information is provided in each interface
   documentation.
*/

/** \brief Corba server communicating with hrp2-genom component.
 *
 This class initializes the Corba server and starts the following Corba interface implementations.
 \li hppCorbaServer::Hrp2Server: to send requests to hrp2-genom component.

 To use this object, call the constructor

 \code
 int argc=1;
 char *argv[1] = {"program"};
 ChppciServer server(argc, argv, isMultiThread);
 \endcode
 where \c isMultiThread specifies whether the server should process
 requests using multi-thread policy of not.

 After starting a name server and configuring your Corba implementation, start the servers.
 \code
 server.startCorbaServer();
 \endcode
 Then, enter in the loop that handle the Corba requests
 \code
 server.processRequest(true);
 \endcode
 You can then send request to the servers.
*/

namespace hpp
{
  namespace corbaServer
  {
    class HPP_CORBASERVER_DLLAPI Server
    {
    public:
      /**
	 \brief Constructor
	 \param inHppPlanner the object that will handle Corba requests.
	 \param argc, argv parameter to feed ORB initialization.
	 \param inMultiThread whether the server may process request using multithred policy.

	 \note It is recommended to configure your Corba implementation through environment
	 variables and to set argc to 1 and argv to any string.

	 \note It is highly recommended not to enable multi-thread policy in CORBA request processing when using
	 hppCorbaServer with KPP interface, since OpenGL is not compatible with multi-threading.

	 \note If multi-thread policy is not selected, request hppCorbaServer::ChppciProblem::interruptPathPlanning
	 will have no effect.
      */
      Server (int argc, const char* argv[], bool multiThread = false);

      /// \brief Shutdown CORBA server
      ~Server ();

      /// \brief Initialize CORBA server to process requests from clients to hpp module
      /// \return 0 if success, -1 if failure.
      int startCorbaServer ();

      /// \brief If ORB work is pending, process it
      /// \param loop if true, the function never returns; if false, the function processes pending requests and returns.
      int processRequest (bool loop);

    private:

      /**
	 \name CORBA server initialization
      */

      /**
	 \brief Initialize ORB and CORBA servers.

	 \param argc, argv parameter to feed ORB initialization.
	 \param inMultiThread whether the server may process request using multithred policy.
      */
      bool initORBandServers (int argc, const char* argv[],
			      bool inMultiThread);

      /**
	 @}
      */
      impl::Server* attPrivate;
    };

  } // end of namespace corbaServer.
} // end of namespace hpp.
#endif