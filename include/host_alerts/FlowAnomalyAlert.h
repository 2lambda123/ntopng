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

#ifndef _FLOW_ANOMALY_ALERT_H_
#define _FLOW_ANOMALY_ALERT_H_

#include "ntop_includes.h"

class FlowAnomalyAlert : public HostAlert {
 private:
  bool is_client_alert;
  u_int32_t value, lower_bound, upper_bound;

  ndpi_serializer* getAlertJSON(ndpi_serializer* serializer) {
    if(serializer == NULL)
      return NULL;
    
    ndpi_serialize_string_boolean(serializer, "is_client_alert", is_client_alert);
    ndpi_serialize_string_uint64(serializer, "value", value);
    ndpi_serialize_string_uint64(serializer, "lower_bound", lower_bound);
    ndpi_serialize_string_uint64(serializer, "upper_bound", upper_bound);
    
    return(serializer);
  }

 public:
  FlowAnomalyAlert(HostCallback *c, Host *h, u_int8_t cli_score, u_int8_t srv_score, bool _is_client_alert, u_int32_t _value, u_int32_t _lower_bound, u_int32_t _upper_bound)
    : HostAlert(c, h, cli_score, srv_score) {
    is_client_alert = _is_client_alert;
    value = _value;
    lower_bound = _lower_bound;
    upper_bound = _upper_bound;
  }
  ~FlowAnomalyAlert() {};

  static HostAlertType getClassType() { return { host_alert_flows_anomaly, alert_category_network }; }
  HostAlertType getAlertType() const  { return getClassType(); }
};

#endif /* _FLOW_ANOMALY_ALERT_H_ */
