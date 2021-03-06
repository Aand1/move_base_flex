/*
 *  Copyright 2017, Magazino GmbH, Sebastian Pütz, Jorge Santos Simón
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *
 *  3. Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *  simple_navigation_server.cpp
 *
 *  authors:
 *    Sebastian Pütz <spuetz@uni-osnabrueck.de>
 *    Jorge Santos Simón <santos@magazino.eu>
 *
 */

#include "move_base_flex/simple_server/simple_navigation_server.h"

namespace move_base_flex
{

SimpleNavigationServer::SimpleNavigationServer(const boost::shared_ptr<tf::TransformListener> &tf_listener_ptr) :
    AbstractNavigationServer(tf_listener_ptr, SimplePlannerExecution::Ptr(new SimplePlannerExecution(condition_)),
                             SimpleControllerExecution::Ptr(new SimpleControllerExecution(condition_, tf_listener_ptr)),
                             SimpleRecoveryExecution::Ptr(new SimpleRecoveryExecution(condition_, tf_listener_ptr)))
{
  // initalize all plugins
  initializeControllerComponents();

  // start all action servers
  startActionServers();
}

SimpleNavigationServer::~SimpleNavigationServer()
{
}

void SimpleNavigationServer::reconfigure(move_base_flex::MoveBaseFlexConfig &config, uint32_t level)
{
  boost::recursive_mutex::scoped_lock sl(configuration_mutex_);
  AbstractNavigationServer::reconfigure(config, level);
}

void SimpleNavigationServer::callActionGetPath(const move_base_flex_msgs::GetPathGoalConstPtr &goal)
{
  AbstractNavigationServer::callActionGetPath(goal);
}

void SimpleNavigationServer::callActionExePath(const move_base_flex_msgs::ExePathGoalConstPtr &goal)
{
  AbstractNavigationServer::callActionExePath(goal);
}

void SimpleNavigationServer::callActionRecovery(const move_base_flex_msgs::RecoveryGoalConstPtr &goal)
{
  AbstractNavigationServer::callActionRecovery(goal);
}

void SimpleNavigationServer::callActionMoveBase(const move_base_flex_msgs::MoveBaseGoalConstPtr &goal)
{
  AbstractNavigationServer::callActionMoveBase(goal);
}

} /* namespace move_base_flex */
