/*
 *
 * (C) 2013-21 - ntop.org
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#ifndef _FLOW_ANOMALY_H_
#define _FLOW_ANOMALY_H_

#include "ntop_includes.h"

class FlowAnomaly : public HostCheck {
private:
  
public:
  FlowAnomaly();
  ~FlowAnomaly() {};

  FlowAnomalyAlert *allocAlert(HostCheck *c, Host *h, risk_percentage cli_pctg, u_int32_t _value, u_int32_t _lower_bound, u_int32_t _upper_bound) {
    FlowAnomalyAlert *alert = new FlowAnomalyAlert(c, h, cli_pctg, _value, _lower_bound, _upper_bound);

    return alert;
  };

  bool loadConfiguration(json_object *config);
  void periodicUpdate(Host *h, HostAlert *engaged_alert);
  
  HostCheckID getID() const { return host_check_flow_anomaly; }
  std::string getName()  const { return(std::string("flows_anomaly")); }
};

#endif
