--
-- (C) 2013-21 - ntop.org
--

local dirs = ntop.getDirs()
package.path = dirs.installdir .. "/scripts/lua/modules/?.lua;" .. package.path
package.path = dirs.installdir .. "/scripts/lua/modules/alert_store/?.lua;" .. package.path

local alert_utils = require "alert_utils"
local alert_consts = require "alert_consts"
local alert_entities = require "alert_entities"
local rest_utils = require("rest_utils")
local flow_alert_store = require "flow_alert_store".new()
local alert_severities = require "alert_severities"

--
-- Read alerts data
-- Example: curl -u admin:admin -H "Content-Type: application/json" -d '{"ifid": "1"}' http://localhost:3000/lua/rest/v1/get/flow/alert/ts.lua
--
-- NOTE: in case of invalid login, no error is returned but redirected to login
--

local rc = rest_utils.consts.success.ok

local ifid = _GET["ifid"]

if isEmptyString(ifid) then
   rc = rest_utils.consts.err.invalid_interface
   rest_utils.answer(rc)
   return
end

interface.select(ifid)

local res = {}
res.series = {} 

for _, severity in pairs(alert_severities) do
   local count_by_time = flow_alert_store:count_by_time(severity.severity_id)
   res.series[#res.series + 1] = { data = count_by_time, name = i18n(severity.i18n_title) }
end

rest_utils.answer(rc, res)
