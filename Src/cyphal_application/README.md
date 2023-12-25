The node has the following interface:

| №  | Type | Message | Topic name  |
| -- | ---- | ------- | ----------- |
|   1 | sub | reg.udral.physics.optics.HighColor.0.1 | lights | {'type': 'Port', 'data_type': 'reg.udral.physics.optics.HighColor.0.1', 'enum_base': 'RGBLED'}|
|   2 | pub | uavcan.si.sample.temperature.Scalar.1.0 | crct.temp | {'type': 'Port', 'data_type': 'uavcan.si.sample.temperature.Scalar.1.0', 'enum_base': 'PARAM_CRCT_TEMPERATURE'}|

The node has the following registers:

| №  | Register name           | Description |
| -- | ----------------------- | ----------- |
|  1 | uavcan.node.id          | Defines a node-ID. Allowed values [0,127]. |
|  2 | system.name             | Defines custom node name. If empty, the node will use the default name. |
|  3 | uavcan.node.description | User/integrator-defined, human-readable description of this specific node. |
|  4 | example.integer         | Just an integer register example |
|  5 | example.string          | Just a string register example |

> This docs was automatically generated. Do not edit it manually.

