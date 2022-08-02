/*****************************************************************************
 * Copyright (C) The Apache Software Foundation. All rights reserved.        *
 * ------------------------------------------------------------------------- *
 * This software is published under the terms of the Apache Software License *
 * version 1.1, a copy of which has been included  with this distribution in *
 * the LICENSE file.                                                         *
 *****************************************************************************/
package org.apache.cocoon.selection;

import org.apache.avalon.framework.activity.Initializable;

/**
 * @version CVS $Revision: 1.2 $ $Date: 2002/01/11 17:07:06 $
 * @deprecated Replaced by RequestParameterSelector - code factories should no longer be used
 */

public class RequestSelectorFactory extends RequestSelector implements Initializable {

    public void initialize() {
        getLogger().warn("RequestSelectorFactory is deprecated. Please use RequestParameterSelector");
    }
}
