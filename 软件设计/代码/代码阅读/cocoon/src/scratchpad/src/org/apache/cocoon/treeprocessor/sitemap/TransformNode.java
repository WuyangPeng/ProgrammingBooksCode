/*****************************************************************************
 * Copyright (C) The Apache Software Foundation. All rights reserved.        *
 * ------------------------------------------------------------------------- *
 * This software is published under the terms of the Apache Software License *
 * version 1.1, a copy of which has been included  with this distribution in *
 * the LICENSE file.                                                         *
 *****************************************************************************/

package org.apache.cocoon.treeprocessor.sitemap;

import org.apache.cocoon.environment.Environment;
import org.apache.cocoon.sitemap.PatternException;

import org.apache.cocoon.treeprocessor.AbstractProcessingNode;
import org.apache.cocoon.treeprocessor.InvokeContext;
import org.apache.cocoon.treeprocessor.MapStackResolver;
import org.apache.cocoon.treeprocessor.ParameterizableProcessingNode;
import org.apache.cocoon.treeprocessor.ProcessingNode;

import java.util.List;
import java.util.Map;

/**
 *
 * @author <a href="mailto:sylvain@apache.org">Sylvain Wallez</a>
 * @version CVS $Revision: 1.3 $ $Date: 2002/01/30 14:35:07 $
 */

public class TransformNode extends AbstractProcessingNode implements ParameterizableProcessingNode {

    private String transformerName;
    
    private MapStackResolver source;
    
    private Map parameters;
    
    private Map views;
    
    public TransformNode(String name, String source) throws PatternException {
        this.transformerName = name;
        this.source = MapStackResolver.getResolver(source);
    }
       
    public void setParameters(Map parameterMap) {
        this.parameters = parameterMap;
    }

    public void setViews(Map views) {
        this.views = views;
    }
    
    public final boolean invoke(Environment env, InvokeContext context)
      throws Exception {
        
        List mapStack = context.getMapStack();
        
        context.getEventPipeline().addTransformer(
            this.transformerName,
            source.resolve(mapStack),
            MapStackResolver.buildParameters(this.parameters, mapStack)
        );
        
        // Check view
        if (this.views != null) {
            String cocoonView = env.getView();
            if (cocoonView != null) {
                
                // Get view node
                ProcessingNode viewNode = (ProcessingNode)this.views.get(cocoonView);
                
                if (viewNode != null) {
                    if (getLogger().isInfoEnabled()) {
                        getLogger().info("Jumping to view " + cocoonView + " from transformer at " + this.getLocation());
                    }
                    return viewNode.invoke(env, context);
                }
            }
        }
        
        // Return false to contine sitemap invocation
        return false;
    }    
}
