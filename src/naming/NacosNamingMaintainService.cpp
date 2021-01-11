#include "src/naming/NacosNamingMaintainService.h"
#include "src/security/SecurityManager.h"

using namespace std;

namespace nacos{

NacosNamingMaintainService::NacosNamingMaintainService(ObjectConfigData *objectConfigData) {
    _objectConfigData = objectConfigData;
    if (_objectConfigData->_appConfigManager->nacosAuthEnabled()) {
        _objectConfigData->_securityManager->login();
        _objectConfigData->_securityManager->start();
    }
}

bool NacosNamingMaintainService::updateInstance
(
    const NacosString &serviceName,
    const NacosString & groupName,
    const Instance &instance
) throw(NacosException) {
    Instance paramInstance = instance;
    paramInstance.serviceName = serviceName;
    paramInstance.groupName = groupName;
    return _objectConfigData->_serverProxy->updateServiceInstance(paramInstance);
}

ServiceInfo2 NacosNamingMaintainService::queryService
(
    const NacosString &serviceName,
    const NacosString &groupName
) throw(NacosException) {
    return _objectConfigData->_serverProxy->getServiceInfo(serviceName, groupName);
}

bool NacosNamingMaintainService::createService(const ServiceInfo2 &service, naming::Selector *selector) throw(NacosException) {
    ServiceInfo2 parmServiceInfo = service;
    if (!parmServiceInfo.isGroupNameSet()) {
        parmServiceInfo.setGroupName(ConfigConstant::DEFAULT_GROUP);
    }
    return _objectConfigData->_serverProxy->createServiceInfo(parmServiceInfo, selector);
}

bool NacosNamingMaintainService::deleteService(const NacosString &serviceName, const NacosString &groupName) throw(NacosException) {
    return _objectConfigData->_serverProxy->deleteServiceInfo(serviceName, groupName);
}

bool NacosNamingMaintainService::updateService(const ServiceInfo2 &service, naming::Selector *selector) throw(NacosException) {
    return _objectConfigData->_serverProxy->updateServiceInfo(service, selector);
}

NacosNamingMaintainService::~NacosNamingMaintainService() {
    delete _objectConfigData;
}

}//namespace nacos
