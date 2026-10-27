# ApplicationInsights Node.js Native Metrics

> **Retirement notice:** This repository is being prepared for archival and is no longer accepting new contributions or feature requests. For Node.js runtime metrics, use upstream OpenTelemetry's [`@opentelemetry/instrumentation-runtime-node`](https://github.com/open-telemetry/opentelemetry-js-contrib/tree/main/packages/instrumentation-runtime-node). For Azure Monitor Application Insights integration, use the [Microsoft OpenTelemetry Distro for Node.js](https://learn.microsoft.com/en-us/azure/azure-monitor/app/opentelemetry-enable?tabs=nodejs) (`@microsoft/opentelemetry`).

Native Metrics Agent for the Application Insights Node.js SDK

## Upstream OpenTelemetry runtime metrics

We recommend [`@opentelemetry/instrumentation-runtime-node`](https://github.com/open-telemetry/opentelemetry-js-contrib/tree/main/packages/instrumentation-runtime-node) as the upstream OpenTelemetry alternative for collecting Node.js runtime metrics, including event-loop utilization and delay, garbage-collection duration, and V8 heap memory.

```sh
npm install @opentelemetry/instrumentation-runtime-node
```

Follow the [upstream setup and compatibility documentation](https://github.com/open-telemetry/opentelemetry-js-contrib/tree/main/packages/instrumentation-runtime-node#readme) to register `RuntimeNodeInstrumentation` with your OpenTelemetry SDK and configure a metrics reader and exporter. The package collects metrics; it does not configure export to Application Insights by itself. If your distro or auto-instrumentation setup already enables this instrumentation, do not register it again or start a second SDK.

This is not a drop-in replacement for the `applicationinsights-native-metrics` API. Review the supported Node.js versions and metric names, units, and aggregation behavior, and update dashboards and alerts as needed.

## Migrate to Microsoft OpenTelemetry Distro

Use the Microsoft OpenTelemetry Distro to collect telemetry and send it to Azure Monitor Application Insights. The `applicationinsights-native-metrics` package is not required by the distro.

1. Review the [Application Insights migration guidance](https://learn.microsoft.com/en-us/azure/azure-monitor/app/migrate-to-opentelemetry?tabs=nodejs) for changes to instrumentation, configuration, and available telemetry. The distro is not a drop-in replacement for this native metrics add-on.
2. Remove `applicationinsights-native-metrics` if it is a direct dependency, and install the distro:

   ```sh
   npm uninstall applicationinsights-native-metrics
   npm install @microsoft/opentelemetry
   ```

3. Follow the [Node.js setup instructions](https://learn.microsoft.com/en-us/azure/azure-monitor/app/opentelemetry-enable?tabs=nodejs) to initialize the distro before loading application libraries and configure your Application Insights connection string. Replace the previous Application Insights SDK initialization rather than running both instrumentation paths together.
4. Verify the telemetry your application relies on before deploying the migration. Do not assume that all native metrics have equivalent replacements.

Applications already using the Azure Monitor OpenTelemetry Distro do not need to switch distros as part of this repository's retirement.

## Contributing

This repository is being prepared for archival and is no longer accepting new contributions. See [SUPPORT.md](SUPPORT.md) for migration and support resources.

The following contribution requirements are retained for reference. Most contributions require you to
agree to a Contributor License Agreement (CLA) declaring that you have the right to,
and actually do, grant us the rights to use your contribution. For details, visit
https://cla.microsoft.com.

When you submit a pull request, a CLA-bot will automatically determine whether you need
to provide a CLA and decorate the PR appropriately (e.g., label, comment). Simply follow the
instructions provided by the bot. You will only need to do this once across all repositories using our CLA.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/)
or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

## Data Collection

As this SDK is designed to enable applications to perform data collection which is sent to the Microsoft collection endpoints the following is required to identify our privacy statement.

The software may collect information about you and your use of the software and send it to Microsoft. Microsoft may use this information to provide services and improve our products and services. You may turn off the telemetry as described in the repository. There are also some features in the software that may enable you and Microsoft to collect data from users of your applications. If you use these features, you must comply with applicable law, including providing appropriate notices to users of your applications together with a copy of Microsoft’s privacy statement. Our privacy statement is located at https://go.microsoft.com/fwlink/?LinkID=824704. You can learn more about data collection and use in the help documentation and our privacy statement. Your use of the software operates as your consent to these practices.

## Trademarks

This project may contain trademarks or logos for projects, products, or services. Authorized use of Microsoft trademarks or logos is subject to and must follow [Microsoft’s Trademark & Brand Guidelines](https://www.microsoft.com/en-us/legal/intellectualproperty/trademarks/usage/general). Use of Microsoft trademarks or logos in modified versions of this project must not cause confusion or imply Microsoft sponsorship. Any use of third-party trademarks or logos are subject to those third-party’s policies.

## License

[MIT](LICENSE)
