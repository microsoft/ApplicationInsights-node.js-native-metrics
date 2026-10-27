# Support

## Repository retirement

This repository is being prepared for archival. For Node.js runtime metrics, migrate from `applicationinsights-native-metrics` to upstream OpenTelemetry's [`@opentelemetry/instrumentation-runtime-node`](https://github.com/open-telemetry/opentelemetry-js-contrib/tree/main/packages/instrumentation-runtime-node). For Azure Monitor Application Insights integration, use the **Microsoft OpenTelemetry Distro for Node.js** (`@microsoft/opentelemetry`).

See the [upstream runtime metrics guidance](README.md#upstream-opentelemetry-runtime-metrics), the [distro migration steps](README.md#migrate-to-microsoft-opentelemetry-distro), the [Application Insights migration guidance](https://learn.microsoft.com/en-us/azure/azure-monitor/app/migrate-to-opentelemetry?tabs=nodejs), and the [Node.js setup instructions](https://learn.microsoft.com/en-us/azure/azure-monitor/app/opentelemetry-enable?tabs=nodejs).

## How to get help

Do not open new feature requests or support issues in this repository. After archival, the repository will be read-only and existing issues and source code will remain available for reference.

For help with Azure Monitor Application Insights, see [how to create an Azure support request](https://learn.microsoft.com/en-us/azure/azure-portal/supportability/how-to-create-azure-support-request).

For help with upstream OpenTelemetry runtime instrumentation, see its [documentation](https://github.com/open-telemetry/opentelemetry-js-contrib/tree/main/packages/instrumentation-runtime-node#readme) and [OpenTelemetry JavaScript discussions](https://github.com/open-telemetry/opentelemetry-js/discussions).

For security vulnerability reporting, continue to follow [SECURITY.md](SECURITY.md).